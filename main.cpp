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
string replaceCode(string &original);

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
	GtkWidget* htmlButton = gui.createButton("HTML to ASCII",330, 80);
	
	//Add eventlisteners handle button clicks
	g_signal_connect (csharpButton,"clicked",G_CALLBACK(openFile),NULL);
	
	//Create entry for path 
	guiEntry = gui.createEntry(330,0,30);
	
	//Create Text view to store the new code in
	guiTextView = gui.createTextView();
	
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
	myFile.open(path.c_str());

	if(myFile.is_open())
	{ 
		string textFile ((istreambuf_iterator<char>(myFile)),istreambuf_iterator<char>());
		keywords.highlightCSharp(textFile);
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
		gtk_text_buffer_set_text(buffer,textFile.c_str(),-1);
		myFile.close();
	}
	else
	{
		string str = path+" was not found!\nPlease fill in a valid path";
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
		gtk_text_buffer_set_text(buffer,str.c_str(),-1);  
	}
}
