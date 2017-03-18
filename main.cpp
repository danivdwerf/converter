#include <iostream>
#include <fstream>
#include <string>

#include <gtkmm.h>
#include <gtk/gtk.h>

#include "gui.h"
#include "keywords.h"

using namespace std;
using namespace Gtk;

string lines,word,path;
ifstream myFile;

Keywords keywords;
CreateGui gui;

GtkWidget* guiWindow;
GtkWidget* guiEntry;
GtkWidget* guiTextView;
GtkWidget* scroller;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;

void openError(string message)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	gtk_text_buffer_set_text(buffer, message.c_str(), -1);
}

static void fileChooser(GtkWidget* button, gpointer window)
{
	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	gtk_widget_show_all(dialog);
	int resp=gtk_dialog_run(GTK_DIALOG(dialog));

	if(resp==GTK_RESPONSE_OK)
	{
		gtk_entry_set_text(GTK_ENTRY(guiEntry),gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
		gtk_widget_destroy(dialog);
	}
	else
	{
		gtk_widget_destroy(dialog);
	}
}

string getExtension(const string& path)
{
		if(path.find_last_of(".") != string::npos)
		{
			return path.substr(path.find_last_of(".")+1);
		}
		else
		{
			return "";
		}
}

void openFile()
{
	if(path == "")
	{
		path = gtk_entry_get_text(GTK_ENTRY(guiEntry));
	}

    DIR* dir;
    if((dir = opendir(path.c_str())) != NULL)
    {
		closedir(dir);
		openError(path + " is a directory!\nPlease fill in a path to a valid file");
	}
	else
	{
		myFile.open(path.c_str());

		if(myFile.is_open())
		{
			string textFile ((istreambuf_iterator<char>(myFile)),istreambuf_iterator<char>());
			string extension = getExtension(path);
			keywords.highlight(extension, textFile);
			GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
			gtk_text_buffer_set_text(buffer,textFile.c_str(),-1);
			myFile.close();
		}
		else
		{
			openError(path + " was not found!\nPlease fill in a valid path");
		}
	}
	path = "";
}

int main(int argc,char* argv[])
{
	//initalize gtk
	gtk_init(&argc,&argv);

	//Create the window
	guiWindow = gui.createWindow(640, 360, "FTDConverter");
	gtk_widget_set_name(guiWindow, "window");

	//Create the fixed container
	GtkWidget* guiFixed = gui.createContainer();

	//Create the buttons to convert the file
	GtkWidget* fileButton = gui.createButton("Choose a file", 330, 40);
	gtk_widget_set_name(fileButton, "fileButton");

	GtkWidget* convertButton = gui.createButton("Convert your code",330, 80);
	gtk_widget_set_name(convertButton, "convertButton");

	//Add eventlisteners handle button clicks
	g_signal_connect (convertButton, "clicked", G_CALLBACK(openFile),NULL);
	g_signal_connect (fileButton, "clicked", G_CALLBACK(fileChooser),guiWindow);

	//Create entry for path
	guiEntry = gui.createEntry(330, 0 , 30, "Fill in the path to your file...");
	gtk_widget_set_name(guiEntry, "inputField");

	//Create Text view to store the new code in
	guiTextView = gui.createTextView("Fill in the path to your file, or click the choose a file button.\n\nAfter selecting your file, your converted code will be show here after converting.\n\nClick within the window and press cmd+c (ctrl+c) to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#\n\nThis software is part of: www.freetimedev.com");
	gtk_widget_set_name(guiTextView, "textWindow");

	//Make textview scrollable, so it won't mess up the window
	scroller = gui.createScroller(0, 0, 320, 350, guiTextView);
	gtk_widget_set_name(scroller, "scrollingWindow");

	//Create a new cssProvider
	provider = gtk_css_provider_new ();
	//Create get the display
	display = gdk_display_get_default ();
	//Get the screen
	screen = gdk_display_get_default_screen (display);

	//Add th cssProvider to to screen
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	//Load the css file
	GError *error = 0;
	gtk_css_provider_load_from_file(provider, g_file_new_for_path("stylesheet.css"), &error);
	g_object_unref (provider);

	//Show all widgets
	gtk_widget_show_all (guiWindow);
	gtk_main ();

	return 0;
}
