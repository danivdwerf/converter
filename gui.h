#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <iostream>
#include <gtk/gtk.h>
using namespace Gtk;

class CreateGui
{
	public:GtkWidget* window;
	public:GtkWidget* fixed;
	public:GtkWidget* button;
	public:GtkWidget* entry;
	public:GtkWidget* textView;
	public:GdkColor colour;
	
	public:GtkWidget* createWindow();
	public:GtkWidget* createContainer();
	public:GtkWidget* createButton();
	public:GtkWidget* createEntry();
	public:GtkWidget* createTextView();
	public:void destroyWidget(GtkWidget* widget); 
};
#endif 