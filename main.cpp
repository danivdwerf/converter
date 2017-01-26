#include <iostream>
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <fstream>
#include <string>
#include "gui.h"

using namespace std;
using namespace Gtk;

string lines,word,final,path;
ifstream myFile;

GtkWidget* guiWindow;
GtkWidget* guiButton;
GtkWidget* guiEntry;
GtkWidget* guiTextView;

void openFile();
string replaceCode(string &original);

int main(int argc,char* argv[])
{
	CreateGui creater;
  //initalize gtk
	gtk_init(&argc,&argv);
	
	//Create the window	
	guiWindow = creater.createWindow();
  //Create the fixed container
  GtkWidget* guiFixed = creater.createContainer();
  //Create the submit button
  guiButton = creater.createButton();
  //Add an eventlistener to the button to handle the click
  g_signal_connect (guiButton,"clicked",G_CALLBACK(openFile),NULL);
  //Create form entry
  guiEntry = creater.createEntry();
  //Create Text view to paste the ascii code
  guiTextView = creater.createTextView();
  
  //show the window  
	gtk_widget_show (guiWindow);
  gtk_main ();
  
  //end the main function
  return 0;
}

void openFile()
{  
    string path = gtk_entry_get_text(GTK_ENTRY(guiEntry));
    myFile.open(path.c_str());
    if(myFile.is_open())
    { 
        string textFile ((istreambuf_iterator<char>(myFile)),istreambuf_iterator<char>());
        final = replaceCode(textFile);
        GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
        gtk_text_buffer_set_text(buffer,final.c_str(),-1);
        myFile.close();
    }
    else
    {
        string str = path+" could not be opened. Does the file exist?";
        GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(guiTextView));
        gtk_text_buffer_set_text(buffer,str.c_str(),-1);  
    }
}

string replaceCode(string &original)
{
    const string toReplace[] = {"<",">","GameObject", "var ","private","public","int ","float","Transform","Instantiate","Destroy","return","Quaternion","void","Update","Start","OnCollisionEnter","OnTriggerEnter","StartCoroutine","IEnumerator","Vector3","Random","Range","GetComponent","yield","identity","position","transform","if(","[SerializeField] ","Awake","using ","FindObjectOfType","GetComponentInChildren","GetComponentsInChildren","GetComponent","OnCollisionStay","OnCollisionExit","CompareTag","LoadSceneAsync","SceneManager","AsyncOperation","progress","get ","set ","Button","onClick","AddListener","delegate","Length","Add","true","false","#include","struct","char","printf","gets","strcpy","fopen","fprintf","fclose","main"};
    const string replaceWith[] = {"&lt;","&gt;","<span class='blue_code'>GameObject</span>", "<span class='pink_code'>var</span> ","<span class='pink_code'>private</span>","<span class='pink_code'>public</span>"," <span class='pink_code'>int</span> ","<span class='pink_code'>float</span>","<span class='blue_code'>Transform</span>","<span class='orange_code'>Instantiate</span>","<span class='orange_code'>Destroy</span>","<span class='pink_code'>return</span>","<span class='blue_code'>Quaternion</span>","<span class='pink_code'>void</span>","<span class='orange_code'>Update</span>","<span class='orange_code'>Start</span>"," <span class='orange_code'>OnCollisionEnter</span> "," <span class='orange_code'>OnTriggerEnter</span> "," <span class='orange_code'>StartCoroutine</span> "," <span class='blue_code'>IEnumerator</span> "," <span class='blue_code'>Vector3</span> "," <span class='blue_code'>Random</span> "," <span class='orange_code'>Range</span> "," <span class='orange_code'>GetComponent</span> "," <span class='pink_code'>yield</span> "," <span class='green_code'>identity</span> "," <span class='green_code'>position</span> "," <span class='green_code'>transform</span> "," <span class='pink_code'>if</span> "," <span class='green_code'>SerializeField</span> "," <span class='orange_code'>Awake</span> "," <span class='pink_code'>using</span> "," <span class='orange_code'>FindObjectOfType</span> "," <span class='orange_code'>GetComponentInChildren</span> "," <span class='orange_code'>GetComponentsInChildren</span> "," <span class='orange_code'>GetComponent</span> "," <span class='orange_code'>OnCollisionStay</span> "," <span class='orange_code'>OnCollisionExit</span> "," <span class='orange_code'>CompareTag</span> "," <span class='orange_code'>LoadSceneAsync</span> "," <span class='blue_code'>SceneManager</span> "," <span class='blue_code'>AsyncOperation</span> "," <span class='blue_code'>progress</span> "," <span class='pink_code'>get</span> "," <span class='pink_code'>set</span> "," <span class='blue_code'>Button</span> "," <span class='green_code'>onClick</span> "," <span class='orange_code'>AddListener</span> "," <span class='pink_code'>delegate</span> "," <span class='orange_code'>Length</span> "," <span class='orange_code'>Add</span> "," <span class='pink_code'>true</span> "," <span class='pink_code'>false</span> ","<span class='pink_code'>#include</span>","<span class='blue_code'>struct</span>","<span class='pink_code'>char</span>","<span class='orange_code'>printf</span>","<span class='orange_code'>gets</span>","<span class='orange_code'>strcpy</span>","<span class='orange_code'>fopen</span>","<span class='orange_code'>fprintf</span>","<span class='orange_code'>fclose</span>","<span class='orange_code'>main</span>"};
    
    for(int i=0;i<(sizeof(toReplace)/sizeof(*toReplace));i++)
    {
        size_t start_pos=0;
        while((start_pos = original.find(toReplace[i], start_pos)) != string::npos) 
        {
            original.replace(start_pos, toReplace[i].length(), replaceWith[i]);
            start_pos += replaceWith[i].length();
        }
    }
    return original;
}
