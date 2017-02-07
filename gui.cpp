#include "gui.h" 
#include <gtkmm.h>
#include <iostream>
#include <gtk/gtk.h>
#include <string>
using namespace Gtk;
using namespace std;

	GtkWidget* window;
	GtkWidget* fixed;
	GtkWidget* button;
	GtkWidget* entry;
	GtkWidget* textView;
	GtkWidget* dialog;
	GdkColor colour;

	GtkWidget* CreateGui::createWindow(int width, int height, string title)
	{   
		colour.red = 0x3333;
		colour.green = 0x3333;
 		colour.blue = 0x3333;
 		
 		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 		
 		gtk_widget_set_size_request(window, width,height);
 		gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
 		
 		gtk_window_set_title (GTK_WINDOW (window), title.c_str());
 		gtk_container_set_border_width (GTK_CONTAINER (window), 10);
		gtk_widget_modify_bg(window,GTK_STATE_NORMAL,&colour);
		
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

	GtkWidget* CreateGui::createButton(string label, int x, int y)
	{
 		button = gtk_button_new_with_label (label.c_str());
		gtk_fixed_put (GTK_FIXED (fixed), button, x, y);
		gtk_widget_show (button);
		return button;
	}

	GtkWidget* CreateGui::createEntry(int x, int y, int width, string placeholder)
	{
		entry = gtk_entry_new();
		gtk_fixed_put(GTK_FIXED(fixed),entry,x,y);
		gtk_entry_set_width_chars(GTK_ENTRY(entry),width);
		gtk_entry_set_text(GTK_ENTRY(entry),placeholder.c_str());
		gtk_widget_show(entry);
		return entry;
	}

	GtkWidget* CreateGui::createTextView(string text)
	{		
		textView = gtk_text_view_new();
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
		
		gtk_text_buffer_set_text(buffer,text.c_str(),-1);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(textView),false);
		gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView),false);
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView),GTK_WRAP_WORD);
		gtk_widget_show(textView);
		
		return textView;
	}
	
	GtkWidget* CreateGui::createScroller(int width, int height, GtkWidget* widget)
	{
		GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
		gtk_widget_set_size_request(scroll, width, height);
		gtk_container_add(GTK_CONTAINER(scroll), widget);
		gtk_container_add(GTK_CONTAINER(fixed), scroll);
		gtk_fixed_put (GTK_FIXED (fixed), scroll, 0, 0);	
		gtk_widget_show(scroll);   
		return scroll;
	}

	void CreateGui::destroyWidget(GtkWidget* widget)
	{
  	  gtk_widget_destroy(widget);
	}
