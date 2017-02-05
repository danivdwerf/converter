#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <iostream>
#include <gtk/gtk.h>
#include <string>
using namespace Gtk;
using namespace std;
class CreateGui
{
	public:GtkWidget* window;
	public:GtkWidget* fixed;
	public:GtkWidget* button;
	public:GtkWidget* entry;
	public:GtkWidget* textView;
	public:GdkColor colour;
	
	public:GtkWidget* createWindow(int width, int height);
	public:GtkWidget* createContainer();
	public:GtkWidget* createButton(string label, int x, int y);
	public:GtkWidget* createEntry();
	public:GtkWidget* createTextView();
	public:void destroyWidget(GtkWidget* widget); 
};
#endif 
