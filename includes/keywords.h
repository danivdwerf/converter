#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>

class Keywords
{
	private: std::string original;

	private: void highlightCSharp();
	private: void highlightHTML();
	// private: void highlightPHP();
	private: std::string getExtension(const std::string);
	private: bool validType(size_t, int);
	private: void highlightCSharpMethod(size_t, int);

	public: std::string highlight(std::string, std::string&);
};
#endif
