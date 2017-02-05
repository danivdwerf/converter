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
	public:GtkWidget* scroll;
	public:GdkColor colour;
	
	public:GtkWidget* createWindow(int width, int height, string title);
	public:GtkWidget* createContainer();
	public:GtkWidget* createButton(string label, int x, int y);
	public:GtkWidget* createEntry(int x, int y, int width);
	public:GtkWidget* createTextView();
	public:GtkWidget* createScroller(int width, int height, GtkWidget* widget);
	public:void destroyWidget(GtkWidget* widget); 
};
#endif 
