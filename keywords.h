#ifndef KEYWORDS
#define KEYWORDS

#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Keywords
{
	private:
		const vector<string> getCSharpkeywords();
		const vector<string> getCSharpHighlighted();
		void highlightCSharp(string &original);

		const vector<string> getHTMLkeywords();
		const vector<string> getHTMLhighlighted();
		void highlightHTML(string &original);
		string getExtension(const string& path);

	public:
		void highlight(string& path, string& code);
};

#endif
