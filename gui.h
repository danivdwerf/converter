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
	private:GtkWidget* window;
	private:GtkWidget* fixed;
	private:GtkWidget* button;
	private:GtkWidget* entry;
	private:GtkWidget* textView;
	private:GtkWidget* scroll;
	private:GdkColor colour;
	private: GtkWidget* dialog;
	
	public:GtkWidget* createWindow(int width, int height, string title);
	public:GtkWidget* createContainer();
	public:GtkWidget* createButton(string label, int x, int y);
	public:GtkWidget* createEntry(int x, int y, int width, string placeholder);
	public:GtkWidget* createTextView(string text);
	public:GtkWidget* createScroller(int width, int height, GtkWidget* widget);

	public:void destroyWidget(GtkWidget* widget); 
};
#endif 
