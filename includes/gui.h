#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream>

class GUI
{
	public: GtkWidget* createWindow(int, int, bool, std::string, int);
	public: GtkWidget* createContainer(GtkWidget*);
	public: GtkWidget* createButton(std::string, GtkWidget*, int, int, int, int, std::string);
	public: GtkWidget* createEntry(GtkWidget*, int, int, int, std::string);
	public: GtkWidget* createTextView(std::string, bool, bool);
	public: GtkWidget* createScroller(GtkWidget*, int, int, int, int, GtkWidget*);
	public: GtkWidget* createImage(GtkWidget*, std::string, int, int);
	public: GtkTextTag* setTag(GtkWidget*, std::string, int, int);
	public: void setStylesheet(std::string);
	public: void destroyWidget(GtkWidget* widget);
	public: void setText(std::string, GtkWidget*);
};
#endif
