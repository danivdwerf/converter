#ifndef KEYWORDS
#define KEYWORDS

#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Keywords
{
	private: const vector<string> getCSharpkeywords();
	private: const vector<string> getCSharpHighlighted();
	private: void highlightCSharp(string &original);
	
	/*
	private: const vector<string> getHTMLkeywords();
	private: const vector<string> getHTMLhighlighted();
	private: const vector<>string highlightHTML(string &original);
	*/
	
	public: void highlight(string& extension, string& code);
};

#endif
