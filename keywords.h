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
	public: void highlightCSharp(string &original);
};

#endif
