#include "keywords.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const vector<string> Keywords::getCSharpkeywords()
{
	vector<string> temp;

	temp.push_back("<");
	temp.push_back(">");
	temp.push_back("GameObject ");
	temp.push_back("var ");
	temp.push_back("private ");
	temp.push_back("public ");
	temp.push_back("int ");
	temp.push_back("float ");
	temp.push_back("Transform ");
	temp.push_back("Instantiate");
	temp.push_back("Destroy");
	temp.push_back("return ");
	temp.push_back("Quaternion");
	temp.push_back("void ");
	temp.push_back(" Update");
	temp.push_back(" Start");
	temp.push_back(" OnCollisionEnter");
	temp.push_back(" OnTriggerEnter");
	temp.push_back("StartCoroutine");
	temp.push_back("IEnumerator ");
	temp.push_back("Vector3");
	temp.push_back("Random");
	temp.push_back("Range");
	temp.push_back("GetComponent");
	temp.push_back("yield ");
	temp.push_back("identity");
	temp.push_back("position");
	temp.push_back("transform");
	temp.push_back("if(");
	temp.push_back("[SerializeField]");
	temp.push_back(" Awake");
	temp.push_back("using ");
	temp.push_back("FindObjectOfType");
	temp.push_back("GetComponentInChildren");
	temp.push_back("GetComponentsInChildren");
	temp.push_back("GetComponent");
	temp.push_back("OnCollisionStay");
	temp.push_back("OnCollisionExit");
	temp.push_back("CompareTag");
	temp.push_back("LoadSceneAsync");
	temp.push_back("SceneManager");
	temp.push_back("AsyncOperation");
	temp.push_back("progress");
	temp.push_back("get");
	temp.push_back("set");
	temp.push_back("Button ");
	temp.push_back("onClick");
	temp.push_back("AddListener");
	temp.push_back("delegate");
	temp.push_back("Length");
	temp.push_back("Add");
	temp.push_back("true");
	temp.push_back("false");
	temp.push_back("#include");
	temp.push_back("struct");
	temp.push_back("char");
	temp.push_back("printf");
	temp.push_back("gets");
	temp.push_back("strcpy");
	temp.push_back("fopen");
	temp.push_back("fprintf");
	temp.push_back("fclose");
	temp.push_back("main");
	return temp;
}

const vector<string> Keywords::getCSharpHighlighted()
{
	vector<string> temp;
	temp.push_back("&lt;");
	temp.push_back("&gt;");
	temp.push_back("<span class='blue_code'>GameObject</span> ");
	temp.push_back("<span class='pink_code'>var</span> ");
	temp.push_back("<span class='pink_code'>private</span> ");
	temp.push_back("<span class='pink_code'>public</span> ");
	temp.push_back("<span class='pink_code'>int</span> ");
	temp.push_back("<span class='pink_code'>float</span> ");
	temp.push_back("<span class='blue_code'>Transform</span> ");
	temp.push_back("<span class='orange_code'>Instantiate</span>");
	temp.push_back("<span class='orange_code'>Destroy</span>");
	temp.push_back("<span class='pink_code'>return</span> ");
	temp.push_back("<span class='blue_code'>Quaternion</span>");
	temp.push_back("<span class='pink_code'>void</span> ");
	temp.push_back("<span class='orange_code'> Update</span>");
	temp.push_back("<span class='orange_code'> Start</span>");
	temp.push_back("<span class='orange_code'> OnCollisionEnter</span>");
	temp.push_back("<span class='orange_code'> OnTriggerEnter</span>");
	temp.push_back("<span class='orange_code'>StartCoroutine</span>");
	temp.push_back("<span class='blue_code'>IEnumerator</span> ");
	temp.push_back("<span class='blue_code'>Vector3</span>");
	temp.push_back("<span class='blue_code'>Random</span>");
	temp.push_back("<span class='orange_code'>Range</span>");
	temp.push_back("<span class='orange_code'>GetComponent</span>");
	temp.push_back("<span class='pink_code'>yield</span> ");
	temp.push_back("<span class='green_code'>identity</span>");
	temp.push_back("<span class='green_code'>position</span>");
	temp.push_back("<span class='green_code'>transform</span>");
	temp.push_back("<span class='pink_code'>if</span>(");
	temp.push_back("[<span class='green_code'>SerializeField</span>]");
	temp.push_back("<span class='orange_code'> Awake</span>");
	temp.push_back("<span class='pink_code'>using</span> ");
	temp.push_back("<span class='orange_code'>FindObjectOfType</span>");
	temp.push_back("<span class='orange_code'>GetComponentInChildren</span>");
	temp.push_back("<span class='orange_code'>GetComponentsInChildren</span>");
	temp.push_back("<span class='orange_code'>GetComponent</span>");
	temp.push_back("<span class='orange_code'>OnCollisionStay</span>");
	temp.push_back("<span class='orange_code'>OnCollisionExit</span>");
	temp.push_back("<span class='orange_code'>CompareTag</span>");
	temp.push_back("<span class='orange_code'>LoadSceneAsync</span>");
	temp.push_back("<span class='blue_code'>SceneManager</span>");
	temp.push_back("<span class='blue_code'>AsyncOperation</span>");
	temp.push_back("<span class='blue_code'>progress</span>");
	temp.push_back("<span class='pink_code'>get</span>");
	temp.push_back("<span class='pink_code'>set</span>");
	temp.push_back("<span class='blue_code'>Button</span> ");
	temp.push_back("<span class='green_code'>onClick</span>");
	temp.push_back("<span class='orange_code'>AddListener</span>");
	temp.push_back("<span class='pink_code'>delegate</span>");
	temp.push_back("<span class='orange_code'>Length</span>");
	temp.push_back("<span class='orange_code'>Add</span>");
	temp.push_back("<span class='pink_code'>true</span>");
	temp.push_back("<span class='pink_code'>false</span>");
	temp.push_back("<span class='pink_code'>#include</span>");
	temp.push_back("<span class='blue_code'>struct</span>");
	temp.push_back("<span class='pink_code'>char</span>");
	temp.push_back("<span class='orange_code'>printf</span>");
	temp.push_back("<span class='orange_code'>gets</span>");
	temp.push_back("<span class='orange_code'>strcpy</span>");
	temp.push_back("<span class='orange_code'>fopen</span>");
	temp.push_back("<span class='orange_code'>fprintf</span>");
	temp.push_back("<span class='orange_code'>fclose</span>");
	temp.push_back("<span class='orange_code'>main</span>");
	return temp;
}

void Keywords::highlightCSharp(string &original)
{
	const vector<string> keywords = getCSharpkeywords();
	const vector<string> highlightedKeywords = getCSharpHighlighted();
	for(int i=0;i<keywords.size();i++)
    {
        size_t start_pos=0;
        while((start_pos = original.find(keywords[i], start_pos)) != string::npos)
        {
            original.replace(start_pos, keywords[i].length(), highlightedKeywords[i]);
            start_pos +=highlightedKeywords[i].length();
        }
    }
}

const vector<string> Keywords::getHTMLkeywords()
{
	vector<string> temp;

	temp.push_back("<!DOCTYPE html>");
	temp.push_back("<html");
	temp.push_back("</html>");
	temp.push_back("<head");
	temp.push_back("</head>");
	temp.push_back("<body");
	temp.push_back("</body>");
	temp.push_back("<a");
	temp.push_back("</a>");
	temp.push_back("<table");
	temp.push_back("</table>");
	temp.push_back("<form");
	temp.push_back("</form>");
	temp.push_back("<tbody");
	temp.push_back("</tbody>");
	temp.push_back("<th");
	temp.push_back("</th>");
	temp.push_back("<tr");
	temp.push_back("</tr>");
	temp.push_back("<h1");
	temp.push_back("</h1>");
	temp.push_back("<h2");
	temp.push_back("</h2>");
	temp.push_back("<h3");
	temp.push_back("</h3>");
	temp.push_back("<h4");
	temp.push_back("</h4>");
	temp.push_back("<h5");
	temp.push_back("</h5>");
	temp.push_back("<h6");
	temp.push_back("</h6>");
	temp.push_back("<p");
	temp.push_back("</p>");
	temp.push_back("<meta");
	temp.push_back("<link");
	temp.push_back("<main");
	temp.push_back("</main>");
	temp.push_back("<");
	temp.push_back(">");
	return temp;
}

const vector<string> Keywords::getHTMLhighlighted()
{
	vector<string> temp;

	temp.push_back("&lt;<span class='green_code'>!DOCTYPE html</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>html</span>");
	temp.push_back("&lt;<span class='green_code'>/html</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>head</span>");
	temp.push_back("&lt;<span class='green_code'>/head</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>body</span>");
	temp.push_back("&lt;<span class='green_code'>/body</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>a</span>");
	temp.push_back("&lt;<span class='green_code'>/a</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>table</span>");
	temp.push_back("&lt;<span class='green_code'>/table</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>form</span>");
	temp.push_back("&lt;<span class='green_code'>/form</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>tbody</span>");
	temp.push_back("&lt;<span class='green_code'>/tbody</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>th</span>");
	temp.push_back("&lt;<span class='green_code'>/th</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>tr</span>");
	temp.push_back("&lt;<span class='green_code'>/tr</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h1</span>");
	temp.push_back("&lt;<span class='green_code'>/h1</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h2</span>");
	temp.push_back("&lt;<span class='green_code'>/h2</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h3</span>");
	temp.push_back("&lt;<span class='green_code'>/h3</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h4</span>");
	temp.push_back("&lt;<span class='green_code'>/h4</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h5</span>");
	temp.push_back("&lt;<span class='green_code'>/h5</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>h6</span>");
	temp.push_back("&lt;<span class='green_code'>/h6</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>p</span>");
	temp.push_back("&lt;<span class='green_code'>/p</span>&gt;");
	temp.push_back("&lt;<span class='green_code'>meta</span>");
	temp.push_back("&lt;<span class='green_code'>link</span>");
	temp.push_back("&lt;<span class='green_code'>main</span>");
	temp.push_back("&lt;<span class='green_code'>/main</span>");
	temp.push_back("&lt;");
	temp.push_back("&gt;");
	return temp;
}

void Keywords::highlightHTML(string &original)
{
	const vector<string> keywords = getHTMLkeywords();
	const vector<string> highlightedKeywords = getHTMLhighlighted();

	for(int i=0;i<keywords.size();i++)
    {
        size_t start_pos=0;
        while((start_pos = original.find(keywords[i], start_pos)) != string::npos)
        {
            original.replace(start_pos, keywords[i].length(), highlightedKeywords[i]);
            start_pos +=highlightedKeywords[i].length();
        }
    }
}

void Keywords::highlight(string& extension, string& code)
{
	if(extension=="")
	{
		return;
	}

	if(extension == "cs")
	{
		highlightCSharp(code);
		return;
	}

	if(extension == "html" || extension == "php")
	{
		highlightHTML(code);
		return;
	}
}
