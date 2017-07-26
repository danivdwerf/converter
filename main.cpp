#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include <string>
#include <map>

#include "includes/Resources.h"
#include "includes/keywords.h"
#include "includes/HTTP.h"
#include "includes/gui.h"

#define WINDOW_HEIGHT 360
#define WINDOW_WIDTH 640

std::string version = "1.25";

GtkWidget* window;
GtkWidget* textView;
GtkWidget* entryField;
GtkWidget* scrollWindow;

GUI* gui = new GUI();
HTTP* http = new HTTP();
Keywords* keywords = new Keywords();
Resources* resources = new Resources();

static void fileChooser(GtkWidget* button, gpointer chooser_data)
{
	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show_all(dialog);
	int resp=gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp==GTK_RESPONSE_OK)
		gtk_entry_set_text(GTK_ENTRY(entryField),gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
	gtk_widget_destroy(dialog);
	return;
}

void openFile()
{
	std::string path = "";
	std::ifstream currentFile;
	if(path == "") path = gtk_entry_get_text(GTK_ENTRY(entryField));

  DIR* dir = opendir(path.c_str());
  if(dir != NULL)
  {
		closedir(dir);
		gui->setText("We cannot open directories, please only use paths to files", textView);
		path = "";
		return;
	}

	currentFile.open(path.c_str());
	if(!currentFile.is_open())
	{
		gui->setText("Something went wrong while opening your file :(\nPlease try again", textView);
		path = "";
		return;
	}

	std::string codeFile((std::istreambuf_iterator<char>(currentFile)), std::istreambuf_iterator<char>());
	keywords->highlight(path, codeFile);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	gtk_text_buffer_set_text(buffer, codeFile.c_str(),-1);
	currentFile.close();
	path = "";
	return;
}

void checkUpdate()
{
	try
	{
		std::map<std::string, std::string> headers;
		headers["Header"] = "Le-Skanque";
		std::string values = "clientVersion="+version;
		std::string response = http->sendRequest("http://www.freetimedev.com/SchoolFiles/IDP/FTDConverter/update.php", headers, values);
		if(response == "outdated") gui->setText("New version available!\ndownload newest version from: http://www.freetimedev.com/SchoolFiles/IDP/FTDConverter/FTDConverter.dmg", textView);
	}
	catch(Poco::Exception& e){return;}
}

int main(int argc,char* argv[])
{
	gtk_init(&argc,&argv);
	std::string stylePath = resources->getFilePath("stylesheet.css");
	std::string logoPath = resources->getFilePath("images/logo.png");
	std::string gtkPath = resources->getFilePath("images/GTKLogo.png");

	window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, FALSE, "FTDConverter", 10);
	GtkWidget* fixed = gui->createContainer(window);
	GtkWidget* fileButton = gui->createButton("Choose a file", fixed, 330, 40);
	GtkWidget* convertButton = gui->createButton("Convert your code", fixed, 330, 80);
	entryField = gui->createEntry(fixed, 330, 0 , 30, "Fill in the path to your file...");
	textView = gui->createTextView("Fill in the path to your file, or click the choose a file button.\n\nAfter selecting your file, your converted code will be show here after converting.\n\nSelect your code and press cmd+c (ctrl+c) to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#\n\nThis software is part of: www.freetimedev.com", FALSE, FALSE);
	scrollWindow = gui->createScroller(fixed ,0, 0, 320, 350, textView);
	GtkWidget* ftdLogo = gui->createImage(fixed, logoPath.c_str(), WINDOW_WIDTH - 50,WINDOW_HEIGHT - 50);
	GtkWidget* gtkLogo = gui->createImage(fixed, gtkPath.c_str(), WINDOW_WIDTH - 100, WINDOW_HEIGHT - 50);

	g_signal_connect (convertButton, "clicked", G_CALLBACK(openFile), NULL);
	g_signal_connect (fileButton, "clicked", G_CALLBACK(fileChooser), window);

	GtkCssProvider* provider = gtk_css_provider_new ();
	GdkDisplay* display = gdk_display_get_default ();
	GdkScreen* screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	GError *error = 0;
	gtk_css_provider_load_from_file(provider, g_file_new_for_path(stylePath.c_str()), &error);
	g_object_unref (provider);

	checkUpdate();
	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}
