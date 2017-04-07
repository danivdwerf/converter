#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>

class Keywords
{
	private:
		void highlightCSharp(std::string &);
		void highlightHTML(std::string &);
		std::string getExtension(const std::string&);

	public:
		void highlight(std::string&, std::string&);
};
#endif
