#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtkmm.h>
#include <gtk/gtk.h>

class GUI
{
	public: GtkWidget* createWindow(int, int, bool, std::string, int);
	public: GtkWidget* createContainer(GtkWidget*);
	public: GtkWidget* createButton(std::string, GtkWidget*, int, int);
	public: GtkWidget* createEntry(GtkWidget*, int, int, int, std::string);
	public: GtkWidget* createTextView(std::string, bool, bool);
	public: GtkWidget* createScroller(GtkWidget*, int, int, int, int, GtkWidget*);
	public: GtkWidget* createImage(GtkWidget*, std::string, int, int);
	public: void createConfirmationWindow(GtkWidget*, std::string, int, int);
	// public: static void fileChooser(GtkWidget* button, gpointer window)
	// {
	// 	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	// 	gtk_widget_show_all(dialog);
	// 	int resp=gtk_dialog_run(GTK_DIALOG(dialog));
	// 	if(resp==GTK_RESPONSE_OK)
	// 		gtk_entry_set_text(GTK_ENTRY(entryField),gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
	// 	gtk_widget_destroy(dialog);
	// 	return;
	// }

	public: void destroyWidget(GtkWidget* widget);
	public: void setText(std::string, GtkWidget*);
	public: void addToContainer(GtkWidget*, GtkWidget*);
};
#endif
