#include "gui.h"

GtkWidget* CreateGui::createWindow(int width, int height, std::string title)
{
	//create a new toplevel window
 	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Set the size of the window to the given width and height
 	gtk_widget_set_size_request(window, width, height);
	//Tell the window it can not be resized
 	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//Set the title of the window to the givven string
 	gtk_window_set_title(GTK_WINDOW(window), title.c_str());
	//Set the border of the window
 	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	//Destroy the window when closing the window
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//Return the window
	return window;
}

GtkWidget* CreateGui::createContainer(GtkWidget* window)
{
	//Create a new fixedcontainer
	GtkWidget* fixed = gtk_fixed_new ();
	//Add the container to the window
	gtk_container_add (GTK_CONTAINER (window), fixed);
	//return the container
	return fixed;
}

GtkWidget* CreateGui::createButton(std::string label, GtkWidget* fixed, int xPos, int yPos)
{
	//Create a new button with the given button
 	GtkWidget* button = gtk_button_new_with_label (label.c_str());

	//put the button in the container on the given x and y position
	gtk_fixed_put (GTK_FIXED (fixed), button, xPos, yPos);

	//return the button
	return button;
}

GtkWidget* CreateGui::createEntry(GtkWidget* fixed, int xPos, int yPos, int width, std::string placeholder)
{
	//Create an new entry field
	GtkWidget* entry = gtk_entry_new();
	//put the field in the container on the given x and y position
	gtk_fixed_put(GTK_FIXED(fixed), entry, xPos, yPos);
	//set the width of the entryfield to the given width
	gtk_entry_set_width_chars(GTK_ENTRY(entry), width);
	//Set the placeholder text to the given string
	gtk_entry_set_text(GTK_ENTRY(entry), placeholder.c_str());
	//Return the entry field
	return entry;
}

GtkWidget* CreateGui::createTextView(std::string text)
{
	//Create a new textview
	GtkWidget* textView = gtk_text_view_new();
	//Create a new buffer to store the text for the textview in
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	//Set the text of the buffer to the given text
	gtk_text_buffer_set_text(buffer,text.c_str(), -1);
	//Set if the text should be editable or not
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);
	//Set if the caret should be visible
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textView), FALSE);
	//Set the wrap mode of the textfield
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD);
	//return the textview
	return textView;
}

GtkWidget* CreateGui::createScroller(GtkWidget* fixed, int xPos, int yPos, int width, int height, GtkWidget* widget)
{
	//Create a new scrolling window
	GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
	//Set the width and height to the given values
	gtk_widget_set_size_request(scroll, width, height);
	//Make the scrolling window the container of the given widget
	gtk_container_add(GTK_CONTAINER(scroll), widget);
	//Set the scrolling window to the given values
	gtk_fixed_put (GTK_FIXED (fixed), scroll, xPos, yPos);
	//Return the scrolling window
	return scroll;
}

void CreateGui::destroyWidget(GtkWidget* widget)
{
	//Destroy the given widget
  gtk_widget_destroy(widget);
}
