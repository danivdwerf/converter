#include <iostream>
#include <fstream>
#include <string>
#include <gtkmm.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "keywords.h"

Keywords keywords;

GtkWidget* guiWindow;
GtkWidget* guiEntry;
GtkWidget* guiTextView;
GtkWidget* scroller;

void showError(std::string message)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	gtk_text_buffer_set_text(buffer, message.c_str(), -1);
	return;
}

static void fileChooser(GtkWidget* button, gpointer window)
{
	//Create a new filechooser window
	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	//Make the window visible
	gtk_widget_show_all(dialog);
	//Variable to store the response of the fileChooser
	int resp=gtk_dialog_run(GTK_DIALOG(dialog));
	//Check if the response was OK or Cancel
	if(resp==GTK_RESPONSE_OK)
	{
		//Set the path of the file to the entry field
		gtk_entry_set_text(GTK_ENTRY(guiEntry),gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
	}
	//Destroy the fileChooser window
	gtk_widget_destroy(dialog);
	return;
}

void openFile()
{
	std::string path = "";
	std::ifstream currentFile;
	//Check if the path is empty
	if(path == "")
	{
		//Take the value of the inputField
		path = gtk_entry_get_text(GTK_ENTRY(guiEntry));
	}
	//Open the file as a directory
  DIR* dir = opendir(path.c_str());
	//Check if the directory succeeded to open
  if(dir != NULL)
  {
		//Close the dir, because we only want to allow files.
		closedir(dir);
		//Give the user feedback on why we stopped the highlighting
		showError(path + " is a directory!\nPlease fill in a path to a valid file.");
		//make the path empty again
		path = "";
		return;
	}

	//Open the path as a file
	currentFile.open(path.c_str());
	//Check if it file failed to open
	if(!currentFile.is_open())
	{
		//Give the user feedback on what went wrong
		showError(path + " was not found!\nPlease fill in a valid path");
		//Make the empty again
		path = "";
		return;
	}

	//Get the text from the file
	std::string codeFile ((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
	//Highlight the text
	keywords.highlight(path, codeFile);
	//Create a buffer for the textView
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	//Put the highlighted text in the buffer
	gtk_text_buffer_set_text(buffer, codeFile.c_str(),-1);
	//Close the file
	currentFile.close();
	//Empty the path
	path = "";
	return;
}

int main(int argc,char* argv[])
{
	CreateGui gui;
	//initalize gtk
	gtk_init(&argc,&argv);
	//Create the window
	guiWindow = gui.createWindow(640, 360, FALSE, "FTDConverter");
	//Create the fixed container
	GtkWidget* guiFixed = gui.createContainer(guiWindow);
	//Create the buttons to convert the file
	GtkWidget* fileButton = gui.createButton("Choose a file", guiFixed, 330, 40);
	GtkWidget* convertButton = gui.createButton("Convert your code", guiFixed, 330, 80);
	//Add eventlisteners to handle button clicks
	g_signal_connect (convertButton, "clicked", G_CALLBACK(openFile), NULL);
	g_signal_connect (fileButton, "clicked", G_CALLBACK(fileChooser), guiWindow);
	//Create entry to enter the path in
	guiEntry = gui.createEntry(guiFixed, 330, 0 , 30, "Fill in the path to your file...");
	//Create Text view to store the new code in
	guiTextView = gui.createTextView("Fill in the path to your file, or click the choose a file button.\n\nAfter selecting your file, your converted code will be show here after converting.\n\nSelect your code and press cmd+c (ctrl+c) to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#\n\nThis software is part of: www.freetimedev.com", FALSE, FALSE);
	//Make textview scrollable, so it won't mess up the window
	scroller = gui.createScroller(guiFixed ,0, 0, 320, 350, guiTextView);

	//Load in a extern stylesheet
	GtkCssProvider* provider = gtk_css_provider_new ();
	GdkDisplay *display = gdk_display_get_default ();
	GdkScreen *screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	GError *error = 0;
	gtk_css_provider_load_from_file(provider, g_file_new_for_path("stylesheet.css"), &error);
	g_object_unref (provider);
	//Show all widgets
	gtk_widget_show_all (guiWindow);
	gtk_main ();
	return 0;
}
