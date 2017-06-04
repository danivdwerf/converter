#include <iostream>
#include <fstream>
#include <string>
#include <gtkmm.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "keywords.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

Keywords keywords;

GtkWidget* guiWindow;
GtkWidget* guiEntry;
GtkWidget* guiTextView;
GtkWidget* scroller;

void setText(std::string message)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	gtk_text_buffer_set_text(buffer, message.c_str(), -1);
	return;
}

static void fileChooser(GtkWidget* button, gpointer window)
{
	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show_all(dialog);
	int resp=gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp==GTK_RESPONSE_OK)
		gtk_entry_set_text(GTK_ENTRY(guiEntry),gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));

	gtk_widget_destroy(dialog);
	return;
}

void openFile()
{
	std::string path = "";
	std::ifstream currentFile;
	if(path == "")
		path = gtk_entry_get_text(GTK_ENTRY(guiEntry));

  DIR* dir = opendir(path.c_str());
  if(dir != NULL)
  {
		closedir(dir);
		setText(path + " is a directory!\nPlease fill in a path to a valid file.");
		path = "";
		return;
	}

	currentFile.open(path.c_str());
	if(!currentFile.is_open())
	{
		setText(path + " was not found!\nPlease fill in a valid path");
		path = "";
		return;
	}

	std::string codeFile((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
	keywords.highlight(path, codeFile);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	gtk_text_buffer_set_text(buffer, codeFile.c_str(),-1);
	currentFile.close();
	path = "";
	return;
}

int main(int argc,char* argv[])
{
	CreateGui gui;
	gtk_init(&argc,&argv);
	guiWindow = gui.createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, FALSE, "FTDConverter", 10);
	GtkWidget* guiFixed = gui.createContainer(guiWindow);
	GtkWidget* fileButton = gui.createButton("Choose a file", guiFixed, 330, 40);
	GtkWidget* convertButton = gui.createButton("Convert your code", guiFixed, 330, 80);
	g_signal_connect (convertButton, "clicked", G_CALLBACK(openFile), NULL);
	g_signal_connect (fileButton, "clicked", G_CALLBACK(fileChooser), guiWindow);
	guiEntry = gui.createEntry(guiFixed, 330, 0 , 30, "Fill in the path to your file...");
	guiTextView = gui.createTextView("Fill in the path to your file, or click the choose a file button.\n\nAfter selecting your file, your converted code will be show here after converting.\n\nSelect your code and press cmd+c (ctrl+c) to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#\n\nThis software is part of: www.freetimedev.com", FALSE, FALSE);
	scroller = gui.createScroller(guiFixed ,0, 0, 320, 350, guiTextView);

	GtkWidget* TheImage = gui.createImage(guiFixed, "resources/favicon.ico", WINDOW_WIDTH - 70,WINDOW_HEIGHT - 70);
	GtkCssProvider* provider = gtk_css_provider_new ();
	GdkDisplay *display = gdk_display_get_default ();
	GdkScreen *screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	GError *error = 0;
	gtk_css_provider_load_from_file(provider, g_file_new_for_path("stylesheet.css"), &error);
	g_object_unref (provider);

	gtk_widget_show_all (guiWindow);
	gtk_main ();
	return 0;
}
