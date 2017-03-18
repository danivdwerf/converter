#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>

#include <gtkmm.h>
#include <gtk/gtk.h>

using namespace Gtk;
using namespace std;
class CreateGui
{
	private:
		GtkWidget* window;
		GtkWidget* fixed;
		GtkWidget* button;
		GtkWidget* entry;
		GtkWidget* textView;
		GtkWidget* scroll;
		GtkWidget* dialog;

	public:
		GtkWidget* createWindow(int width, int height, string title);
		GtkWidget* createContainer();
		GtkWidget* createButton(string label, int xPos, int yPos);
		GtkWidget* createEntry(int xPos, int yPos, int width, string placeholder);
		GtkWidget* createTextView(string text);
		GtkWidget* createScroller(int xPos, int yPos, int width, int height, GtkWidget* widget);

		void destroyWidget(GtkWidget* widget);
};
#endif
