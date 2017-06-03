#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtkmm.h>
#include <gtk/gtk.h>

class CreateGui
{
	public:
		GtkWidget* createWindow(int, int, bool, std::string, int);
		GtkWidget* createContainer(GtkWidget*);
		GtkWidget* createButton(std::string, GtkWidget*, int, int);
		GtkWidget* createEntry(GtkWidget*, int, int, int, std::string);
		GtkWidget* createTextView(std::string, bool, bool);
		GtkWidget* createScroller(GtkWidget*, int, int, int, int, GtkWidget*);
		GtkWidget* createImage(GtkWidget*, std::string, int, int);
		void destroyWidget(GtkWidget* widget);
};
#endif
