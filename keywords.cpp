#include "keywords.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>

void Keywords::highlightCSharp(std::string &original)
{
	/*
	std::vector<std::string> asciiChars = {"<",">","public ", "string ", "using ", "bool ", "private "};
	std::vector<std::string> newChar = {"&lt","&gt", "<span class='pink_code'>public</span> ", "<span class='pink_code'>string</span> ","<span class='pink_code'>using</span> ", "<span class='pink_code'>bool</span> ", "<span class='pink_code'>private</span> "};

	for(int i=0;i<asciiChars.size();i++)
	{
		size_t start_pos=0;
		while((start_pos = original.find(asciiChars[i], start_pos)) != string::npos)
		{
			original.replace(start_pos, asciiChars[i].length(), newChar[i]);
			start_pos += newChar[i].length();
		}
	}
	*/

	std::size_t start_pos = 0;
	std::size_t end_pos = 0;
	std::size_t length = 0;
	std::string originalWord = "";
	//Find strings and make them yellow
	while((start_pos = original.find("\"", start_pos)) != std::string::npos)
	{
  	end_pos = original.find_first_of("\"", start_pos+1);
    if (end_pos == std::string::npos)
		{
        break;
		}
    length = end_pos-start_pos;
    originalWord = original.substr(start_pos+1, length-1);
    std::string newWord = "<span class='yellow_code'>\"" + originalWord + "\"</span>";
    original.replace(start_pos, length+1, newWord);
    start_pos = end_pos + 28 + 8;
	}

	//Find comments and make them grey
	start_pos = 0;
	while((start_pos = original.find("/", start_pos)) != std::string::npos)
	{
		if(original.substr(start_pos+1, 1) != "/")
		{
			start_pos++;
			continue;
		}
		end_pos = original.find_first_of("\n", start_pos);
		if (end_pos == std::string::npos)
		{
			start_pos++;
			continue;
		}
		length = end_pos-start_pos;
		originalWord = original.substr(start_pos, length);
		original.replace(start_pos, length, "<span class='comment_code'>"+originalWord+"</span>");
		start_pos = end_pos + 27 + 7;
	}

	//Find classes and make them blue
	for(int i = 0; i < original.size(); i++)
	{
		if(!isupper(original[i]))
		{
			continue;
		}

		if(!isspace(original[i-1]))
		{
			continue;
		}

		start_pos = i;
		end_pos = original.find_first_of("()<>\n;. ", start_pos+1);
		length = end_pos - start_pos;
		originalWord = original.substr(start_pos, length);
		original.replace(start_pos, length, "<span class='blue_code'>"+originalWord+"</span>");
	}

	//Find properties and make them green
	start_pos = 0;
	while((start_pos = original.find(".", start_pos)) != std::string::npos)
	{
			end_pos = original.find_first_of("-+</>*=.;,()[]]", start_pos+1);
			if(end_pos == std::string::npos)
			{
				continue;
			}

			length = end_pos-start_pos;
			originalWord = original.substr(start_pos, length);
			original.replace(start_pos, length, "<span class='green_code'>"+originalWord+"</span>");
			start_pos = end_pos + 25 + 7;
	}
}

void Keywords::highlightHTML(std::string &original)
{
	/*
	for(int i=0;i<keywords.size();i++)
    {
        size_t start_pos=0;
        while((start_pos = original.find(keywords[i], start_pos)) != string::npos)
        {
            original.replace(start_pos, keywords[i].length(), highlightedKeywords[i]);
            start_pos +=highlightedKeywords[i].length();
        }
    }
		*/
}

void Keywords::highlight(std::string& path, std::string& code)
{
	std::string extension = getExtension(path);
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

std::string Keywords::getExtension(const std::string& path)
{
		if(path.find_last_of(".") != std::string::npos)
		{
			return path.substr(path.find_last_of(".")+1);
		}
		else
		{
			return "";
		}
}
