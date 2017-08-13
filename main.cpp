#include <string>
#include <map>

#include "includes/Resources.h"
#include "includes/keywords.h"
#include "includes/HTTP.h"
#include "includes/gui.h"

#define WINDOW_HEIGHT 360
#define WINDOW_WIDTH 640
#define VERSION 1.9

/*GUI variables*/
GtkWidget* textView;
GtkWidget* entryField;

/*Create all insances of classes*/
GUI* gui = new GUI();
HTTP* http = new HTTP();
Keywords* keywords = new Keywords();
Resources* resources = new Resources();

/*Open filechooser window*/
static void fileChooser(GtkWidget* button, gpointer window)
{
	GtkWidget* dialog = gtk_file_chooser_dialog_new("Open a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, "_OK", GTK_RESPONSE_OK, "_CANCEL", GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show_all(dialog);
	int resp = gtk_dialog_run(GTK_DIALOG(dialog));
	if(resp == GTK_RESPONSE_OK)
		gtk_entry_set_text(GTK_ENTRY(entryField), gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
	gtk_widget_destroy(dialog);
	return;
}

/*Dowload the newest version from website*/
void downloadUpdate(GtkTextTag* tag, __attribute__((unused))GObject* object, GdkEvent* event)
{
  GdkEventButton* eventButton = (GdkEventButton*)event;
  if (event->type == GDK_BUTTON_RELEASE && eventButton->button == 1)
    system("open http://www.freetimedev.com/resources/projects/FTDConverter/FTDConverter.dmg");
}

/*Open selected file and highlight code*/
void highlightCode()
{
	gui->setText("Please wait while we run our algorithms", textView);
	std::string path = gtk_entry_get_text(GTK_ENTRY(entryField));
	std::string content = resources->getFileContent(path);
	std::string highlightedCode = keywords->highlight(path, content);
	gui->setText(highlightedCode, textView);
}

/*Check the current version on the website*/
void checkUpdate()
{
	try
	{
		std::map<std::string, std::string> headers;
		headers["Connection"] = "keep-alive";
		std::string values = "clientVersion=" + std::to_string(VERSION);
		std::string response = http->sendRequest("http://freetimedev.com/resources/projects/FTDConverter/update.php", headers, values);
		if(response == "outdated")
		{
			gui->setText("Update available! Click here to download the update", textView);
			GtkTextTag* tag = gui->setTag(textView, "hyperlink", 23, 28);
			g_signal_connect(G_OBJECT(tag), "event", G_CALLBACK(downloadUpdate), NULL);
		}
	}
	catch(Poco::Exception& e){return;}
}

/*Create HTML file with converted code*/
void showExample()
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	GtkTextIter start; gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
	GtkTextIter end; gtk_text_buffer_get_iter_at_offset(buffer, &end, -1);
	std::string highlightedCode = gtk_text_buffer_get_text (buffer, &start, &end, false);

	std::string html = "\0";
	html += "<!DOCTYPE html>\0";
	html += "<head>\0";
	html += "<meta charset='utf-8' />\0";
	html += "</head>\0";
	html += "<html>\0";
	html += "<body>\0";

	html += "<style>\0";
	html += "pre {color: white;padding: 0.5em;margin: 0;background-color: #222;overflow-x: auto;}\0";
	html += "code .pink_code{color: #ff3385;}\0";
	html += "code .blue_code{color: #00bfff;}\0";
	html += "code .orange_code{color: darkorange;}\0";
	html += "code .green_code{color:#00C78C;}\0";
	html += "code .comment_code, code .comment_code *{color:#999 !important;}\0";
	html += "code .purple_code{color: #cc66ff;}\0";
	html += "code .yellow_code{color: #ffe066;}\0";
	html += ".line-number{color:white;display:block;float:left;margin:0 1em 0 -1em;border-right:1px solid;text-align:right;}";
	html += ".line-number span{display:block;padding:0 .5em 0 1em;}";
  html += ".cl{display:block;clear:both;}";
	html += "</style>";

	html += "<pre>\0";
	html += "<code>\0";
	html += highlightedCode;
	html += "</code>\0";
	html += "</pre>\0";

	html += "<script type='text/javascript'>";
	html += "const pre = document.getElementsByTagName('pre');\0";
	html += "for (let i = 0; i < pre.length; i++){\0";
	html += "pre[i].innerHTML = '<span class=\"line-number\"></span>' + pre[i].innerHTML + '<span class=\"cl\"></span>';\0";
	html += "const num = pre[i].innerHTML.split(/\\n/).length;\0";
	html += "for (var j = 0; j < num; j++){\0";
	html +=	"let line_num = pre[i].getElementsByTagName('span')[0];\0";
	html +=	"line_num.innerHTML += '<span>' + (j + 1) + '</span>';\0";
	html += "}};\0";
	html += "</script>";

	html += "</body>\0";

	std::string path = resources->getFilePath("preview.html");
	resources->writeToFile(path, html);
	std::string command = "open " + path;
	system(command.c_str());
}

int main(int argc, char* argv[])
{
	gtk_init(&argc,&argv);

	/*Get paths based on resources folder*/
	std::string stylePath = resources->getFilePath("stylesheet.css");
	std::string logoPath = resources->getFilePath("images/logo.png");
	std::string gtkPath = resources->getFilePath("images/GTKLogo.png");

	/*Create all gui elements*/
	GtkWidget* window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, FALSE, "FTDConverter", 10);
	GtkWidget* fixed = gui->createContainer(window);
	entryField = gui->createEntry(fixed, 405, 0 , 30, "Fill in the path to your file...");
	GtkWidget* fileButton = gui->createButton("Choose a file", fixed, 405, 32, 228, 35, "fileButton");
	GtkWidget* convertButton = gui->createButton("Convert your code", fixed, 405, 64, 228, 35, "convertButton");
	GtkWidget* copyButton = gui->createButton("copy", fixed, 400, 280, 30, 30, "copyButton");
	GtkWidget* exampleButton = gui->createButton("preview", fixed, 400, 318, 50, 30, "copyButton");
	textView = gui->createTextView("Fill in the path to your file, or click the choose a file button.\n\nAfter selecting your file, your converted code will be show here after converting.\n\nSelect your code and press cmd+c (ctrl+c) to copy the text to your clipboard.\n\nAvailable languages are:\nUnityC#", FALSE, FALSE);
	GtkWidget* scrollWindow = gui->createScroller(fixed, 0, 0, 390, 350, textView);

	/*Add logo's*/
	GtkWidget* ftdLogo = gui->createImage(fixed, logoPath.c_str(), WINDOW_WIDTH - 50,WINDOW_HEIGHT - 50);
	GtkWidget* gtkLogo = gui->createImage(fixed, gtkPath.c_str(), WINDOW_WIDTH - 100, WINDOW_HEIGHT - 50);

	/*Add eventlisteners to buttons*/
	g_signal_connect (convertButton, "clicked", G_CALLBACK(highlightCode), NULL);
	g_signal_connect (fileButton, "clicked", G_CALLBACK(fileChooser), window);
	g_signal_connect (copyButton, "clicked", G_CALLBACK(gui->copyBufferToClipboard), textView);
	g_signal_connect (exampleButton, "clicked", G_CALLBACK(showExample), NULL);

	checkUpdate();
	gui->setStylesheet(stylePath);

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}
