#include <iostream>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <fstream>
#include <string>
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

void openFile();
void openError(string message);
string replaceCode(string &original);
string getExtension(const string& path);

int main(int argc,char* argv[])
{
	//initalize gtk
	gtk_init(&argc,&argv);
	
	//Create the window	
	guiWindow = gui.createWindow(640, 360, "FTDConverter");
	
	//Create the fixed container
	GtkWidget* guiFixed = gui.createContainer();
	
	//Create the buttons to convert the file
	GtkWidget* csharpButton = gui.createButton("UnityC# to ASCII",330, 40);
	//GtkWidget* htmlButton = gui.createButton("HTML to ASCII",330, 80);
	
	//Add eventlisteners handle button clicks
	g_signal_connect (csharpButton,"clicked",G_CALLBACK(openFile),NULL);
	
	//Create entry for path 
	guiEntry = gui.createEntry(330,0,30,"Fill in the path to your file...");
	
	//Create Text view to store the new code in
	guiTextView = gui.createTextView("Your converted code will be show here after converting.\n\nClick within the window and press ctrl+c to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#\n\nThis software is part of:\nwww.freetimedev.com");
	
	//Make textview scrollable, so it won't mess up the window
	scroller = gui.createScroller(320, 350, guiTextView);
  
	//show the window  
	gtk_widget_show_all (guiWindow);
	gtk_main ();
  
	return 0;
}

void openFile()
{  
    string path = gtk_entry_get_text(GTK_ENTRY(guiEntry));
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
}

void openError(string message)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
	gtk_text_buffer_set_text(buffer, message.c_str(), -1);  
}

string getExtension(const string& path)
{
		if(path.find_last_of(".") != string::npos)
		{
			return path.substr(path.find_last_of(".")+1);
		}
		else
		{
			return 0;
		}
}
