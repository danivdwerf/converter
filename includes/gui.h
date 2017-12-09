#ifndef GUI_H
#define GUI_H

#include <string>
#include <gtk/gtk.h>
#include <iostream>

class GUI
{
	public: GtkWidget* createWindow(int width, int height, bool rezisable, std::string title, int borderwidth)
	{
		//create a new toplevel window
	 	GtkWidget* temp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		//Set the size of the window to the given width and height
	 	gtk_widget_set_size_request(temp, width, height);
		//Tell the window it can not be resized
	 	gtk_window_set_resizable(GTK_WINDOW(temp), rezisable);
		//Set the title of the window to the givven string
	 	gtk_window_set_title(GTK_WINDOW(temp), title.c_str());
		//Set the border of the window
	 	gtk_container_set_border_width (GTK_CONTAINER(temp), borderwidth);
	  gtk_window_set_position(GTK_WINDOW(temp), GTK_WIN_POS_CENTER);
		//Destroy the window when closing the window
		g_signal_connect(temp, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	  gtk_widget_set_name(temp, "window");
		//Return the window
		return temp;
	}

	public: GtkWidget* createContainer(GtkWidget* window)
	{
		//Create a new fixedcontainer
		GtkWidget* temp = gtk_fixed_new ();
		//Add the container to the window
		gtk_container_add (GTK_CONTAINER (window), temp);
		//return the container
		return temp;
	}

	public: GtkWidget* createButton(std::string label, GtkWidget* fixed, int xPos, int yPos, int width, int height, std::string id = "button")
	{
		//Create a new button with the given button
	 	GtkWidget* temp = gtk_button_new_with_label (label.c_str());
	  gtk_widget_set_size_request(temp, width, height);
		//put the button in the container on the given x and y position
		gtk_fixed_put (GTK_FIXED (fixed), temp, xPos, yPos);
	  gtk_widget_set_name(temp, id.c_str());
		//return the button
		return temp;
	}

	public: GtkWidget* createEntry(GtkWidget* fixed, int xPos, int yPos, int width, std::string placeholder)
	{
		//Create an new entry field
		GtkWidget* temp = gtk_entry_new();
		//put the field in the container on the given x and y position
		gtk_fixed_put(GTK_FIXED(fixed), temp, xPos, yPos);
		//set the width of the entryfield to the given width
		gtk_entry_set_width_chars(GTK_ENTRY(temp), width);
		//Set the placeholder text to the given string
		gtk_entry_set_text(GTK_ENTRY(temp), placeholder.c_str());
	  gtk_widget_set_name(temp, "inputField");
		//Return the entry field
		return temp;
	}

	public: GtkWidget* createTextView(std::string text, bool editable, bool showCursor)
	{
		//Create a new textview
		GtkWidget* temp = gtk_text_view_new();
		//Create a new buffer to store the text for the textview in
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(temp));
		//Set the text of the buffer to the given text
		gtk_text_buffer_set_text(buffer,text.c_str(), -1);
		//Set if the text should be editable or not
		gtk_text_view_set_editable(GTK_TEXT_VIEW(temp), editable);
		//Set if the caret should be visible
		gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(temp), showCursor);
		//Set the wrap mode of the textfield
		gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(temp), GTK_WRAP_WORD);
	  gtk_widget_set_name(temp, "textView");
		//return the textview
		return temp;
	}

	public: GtkWidget* createScroller(GtkWidget* fixed, int xPos, int yPos, int width, int height, GtkWidget* widget)
	{
		//Create a new scrolling window
		GtkWidget* temp = gtk_scrolled_window_new(NULL, NULL);
		//Set the width and height to the given values
		gtk_widget_set_size_request(temp, width, height);
		//Make the scrolling window the container of the given widget
		gtk_container_add(GTK_CONTAINER(temp), widget);
		//Set the scrolling window to the given values
		gtk_fixed_put (GTK_FIXED (fixed), temp, xPos, yPos);
	  gtk_widget_set_name(temp, "scrollingWindow");
		//Return the scrolling window
		return temp;
	}

	public: GtkWidget* createImage(GtkWidget* container, std::string path, int xPos, int yPos)
	{
	  GtkWidget* temp = gtk_image_new_from_file(path.c_str());
	  gtk_fixed_put (GTK_FIXED (container), temp, xPos, yPos);
	  return temp;
	}

	public: GtkTextTag* setTag(GtkWidget* textview, std::string tag, int start_pos, int end_pos)
	{
	  GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
	  GtkTextTag* tempTag = gtk_text_buffer_create_tag (buffer, tag.c_str(), "foreground", "blue", 0);
	  g_assert(GTK_IS_TEXT_TAG(tempTag));

	  GtkTextIter start;
	  gtk_text_buffer_get_iter_at_offset(buffer, &start, start_pos);
	  GtkTextIter end;
	  gtk_text_buffer_get_iter_at_offset(buffer, &end, end_pos);
	  gtk_text_buffer_apply_tag(buffer, tempTag, &start, &end);
	  return tempTag;
	}

	/*Copy content from textview */
	public: static void copyBufferToClipboard(GtkWidget* button, gpointer textView)
	{
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

		GtkTextIter start;
		gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
		GtkTextIter end;
		gtk_text_buffer_get_iter_at_offset(buffer, &end, -1);

		gtk_text_buffer_select_range(buffer, &start, &end);

		GdkAtom atom = gdk_atom_intern ("CLIPBOARD", true);
		GtkClipboard* clipboard = gtk_clipboard_get(atom);
		gtk_text_buffer_copy_clipboard (buffer, clipboard);
	}

	public: void setStylesheet(std::string stylesheet)
	{
	  GtkCssProvider* provider = gtk_css_provider_new ();
	  GdkDisplay* display = gdk_display_get_default ();
	  GdkScreen* screen = gdk_display_get_default_screen (display);
	  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	  GError* error = nullptr;
	  gtk_css_provider_load_from_file(provider, g_file_new_for_path(stylesheet.c_str()), &error);
	  if(error != NULL)
	    std::cout << error-> message << '\n';
	  g_object_unref (provider);
	}

	public: void destroyWidget(GtkWidget* widget){gtk_widget_destroy(widget);}

	public: void setText(std::string message, GtkWidget* textfield)
	{
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textfield));
		gtk_text_buffer_set_text(buffer, message.c_str(), -1);
		return;
	}
};
#endif
