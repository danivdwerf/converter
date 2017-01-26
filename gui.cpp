#include "gui.h" 
#include <gtkmm.h>
#include <iostream>
#include <gtk/gtk.h>

using namespace Gtk;

	GtkWidget* window;
	GtkWidget* fixed;
	GtkWidget* button;
	GtkWidget* entry;
	GtkWidget* textView;
	GdkColor colour;

	GtkWidget* CreateGui::createWindow()
	{   
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  	colour.red = 0x3333;
  	colour.green = 0x3333;
 		colour.blue = 0x3333;
		gtk_widget_modify_bg(window,GTK_STATE_NORMAL,&colour);
  	gtk_window_set_title (GTK_WINDOW (window), "FreeTimeDev.com");
  	gtk_window_resize(GTK_WINDOW(window),640,360);
	  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	  g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	  return window;
	}
	
	GtkWidget* CreateGui::createContainer()
	{
	  fixed = gtk_fixed_new ();
	  gtk_container_add (GTK_CONTAINER (window), fixed);
	  gtk_widget_show (fixed);
	  return fixed;
	}

	GtkWidget* CreateGui::createButton()
	{
 		button = gtk_button_new_with_label ("Convert HTML to ASCII");
  	gtk_fixed_put (GTK_FIXED (fixed), button, 230, 130);
  	gtk_widget_show (button);
  	return button;
	}

	GtkWidget* CreateGui::createEntry()
	{
  	entry = gtk_entry_new();
  	gtk_fixed_put(GTK_FIXED(fixed),entry,50,100);
  	gtk_entry_set_width_chars(GTK_ENTRY(entry),70);
  	gtk_entry_set_text(GTK_ENTRY(entry),"Fill in the path to your file...");
	  gtk_widget_show(entry);
	  return entry;
	}

	GtkWidget* CreateGui::createTextView()
	{
  	textView = gtk_text_view_new();
  	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
  	gtk_text_buffer_set_text(buffer,"Please fill in the ABSOLUTE url to the file you want to convert.",-1);
  	gtk_fixed_put (GTK_FIXED (fixed), textView, 0, 0);
  	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView),false);
  	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView),false);
  	gtk_widget_show(textView);   
  	return textView;
	}

	void CreateGui::destroyWidget(GtkWidget* widget)
	{
  	  gtk_widget_destroy(widget);
	}