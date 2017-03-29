#ifndef KEYWORDS
#define KEYWORDS

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
using namespace std;
class Keywords
{
	private:
		void highlightCSharp(string &original);
		void highlightHTML(string &original);
		string getExtension(const string& path);

	public:
		void highlight(string& path, string& code);
};

#endif
