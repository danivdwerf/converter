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
GtkWidget* guiButton;
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
	guiWindow = gui.createWindow(640, 360);
	//Create the fixed container
	GtkWidget* guiFixed = gui.createContainer();
	//Create the submit button
	guiButton = gui.createButton("UnityC# to ASCII",330, 40);
	//GtkWidget* buttonTwo = gui.createButton("HTML to ASCII",330, 80);
	//Add an eventlistener to the button to handle the click
	g_signal_connect (guiButton,"clicked",G_CALLBACK(openFile),NULL);
	//Create form entry
	guiEntry = gui.createEntry();
	//Create Text view to paste the ascii code
	guiTextView = gui.createTextView();
	
	scroller = gui.createScroller(320, 350);
  
	//show the window  
	gtk_widget_show_all (guiWindow);
	gtk_main ();
  
	//end the main function
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
