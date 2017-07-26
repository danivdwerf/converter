#include "keywords.h"

void Keywords::highlightCSharp(std::string &original)
{
	std::vector<std::string> originalArray ={"<", ">", "if", "using", "int", "float", "string", "double", "char", "void", "private", "public", "protectet", "sealed"};
	std::vector<std::string> colouredWord ={"&lt;", "&gt;", "<span class='pink_code'>if</span>", "<span class='pink_code'>using</span>", "<span class='pink_code'>int</span>", "<span class='pink_code'>float</span>", "<span class='pink_code'>string</span>", "<span class='pink_code'>double</span>", "<span class='pink_code'>char</span>", "<span class='pink_code'>void</span>", "<span class='pink_code'>private</span>", "<span class='pink_code'>public</span>", "<span class='pink_code'>protectet</span>", "<span class='pink_code'>sealed</span>"};
	std::size_t start_pos = 0;
	std::size_t end_pos = 0;
	std::size_t length = 0;

	//Replaces the less than and greather than signs
	for(int i = 0; i < originalArray.size(); i++)
	{
		start_pos = 0;
		while((start_pos = original.find(originalArray[i], start_pos)) != std::string::npos)
		{
			if(originalArray[i] == "<" || originalArray[i] == ">")
			{
				if(original.substr(start_pos+1, 4) == "span" || original.substr(start_pos+1, 5) == "/span")
				{
					start_pos++;
					continue;
				}

				if(original.substr(start_pos-4, 4) == "span" || original.substr(start_pos-5, 5) == "/span")
				{
					start_pos++;
					continue;
				}
			}

			if(originalArray[i] == "if")
			{
				if(original[start_pos + 2] != '(' && original[start_pos + 3] != '(')
				{
					start_pos++;
					continue;
				}
			}

			if(originalArray[i] == "using")
			{
				if(original[start_pos + 5] != ' ' || !isupper(original[start_pos + 6]))
				{
					start_pos++;
					continue;
				}
			}

			if(originalArray[i] == "int" || originalArray[i] == "float" || originalArray[i] == "string" || originalArray[i] == "double" || originalArray[i] == "char")
			{
				if(original[start_pos - 1] != ' '  && original[start_pos - 1] != '{' & original[start_pos - 1] != '(' || original[start_pos + originalArray[i].length()] != ' ' && original[start_pos+3] != '[')
				{
					start_pos++;
					continue;
				}

				size_t methodBegin = start_pos+originalArray[i].length()+1;
				size_t methodEnd = original.find_first_of("(\n=.{", methodBegin);
				if(methodEnd != std::string::npos)
				{
					size_t methodLength = methodEnd - methodBegin;
					std::string method = original.substr(methodBegin, methodLength);
					original.replace(methodBegin, methodLength, "<span class='orange_code'>"+method+"</span>");
				}
			}

			if(originalArray[i] == "void")
			{
				if(original[start_pos -1] != ' ' || original[start_pos + originalArray[i].length()] != ' ')
				{
					start_pos++;
					continue;
				}

				size_t methodBegin = start_pos+originalArray[i].length()+1;
				size_t methodEnd = original.find_first_of("(.=", methodBegin);
				if(methodEnd == std::string::npos)
				{
					start_pos++;
					continue;
				}
				size_t methodLength = methodEnd - methodBegin;
				std::string method = original.substr(methodBegin, methodLength);
				original.replace(methodBegin, methodLength, "<span class='orange_code'>"+method+"</span>");
			}

			if(originalArray[i] == "private" || originalArray[i] == "public" || originalArray[i] == "protected" || originalArray[i] == "sealed")
			{
				if(original[start_pos + originalArray[i].length()] != ' ')
				{
					start_pos++;
					continue;
				}
			}
			original.replace(start_pos, originalArray[i].length(), colouredWord[i]);
			start_pos += colouredWord[i].length();
		}
	}

	std::string originalWord = "";
	//Finding strings
	start_pos=0;
	while((start_pos = original.find("\"", start_pos)) != std::string::npos)
	{
  	end_pos = original.find_first_of("\"", start_pos+1);
    if (end_pos == std::string::npos)
		{
			start_pos++;
      continue;
		}

    length = end_pos-start_pos;
    originalWord = original.substr(start_pos+1, length-1);
    std::string newWord = "<span class='yellow_code'>\"" + originalWord + "\"</span>";
    original.replace(start_pos, length+1, newWord);
    start_pos = end_pos + 28 + 8;
	}

	//Looks for words starting with a cap
	for(int i = 0; i < original.size(); i++)
	{
		start_pos = i;
		if(!isupper(original[start_pos]))
			continue;

		if(!isspace(original[start_pos-1]) && original.substr(start_pos-1, 1) != ";" && original.substr(start_pos-1, 1) != "[")
			continue;

		end_pos = original.find_first_of("[]{}()>\n;&. ", start_pos+1);
		length = end_pos - start_pos;
		originalWord = original.substr(start_pos, length);
		original.replace(start_pos, length, "<span class='blue_code'>"+originalWord+"</span>");
	}

	//Finds words after a period
	start_pos = 0;
	while((start_pos = original.find(".", start_pos)) != std::string::npos)
	{
		if(isdigit(original[start_pos + 1]) && isdigit(original[start_pos - 1]))
		{
			start_pos++;
			continue;
		}

		size_t methodBegin = start_pos+1;
		size_t methodEnd = original.find_first_of("({\n.=", methodBegin);
		if(methodEnd != std::string::npos)
		{
			size_t methodLength = methodEnd - methodBegin;
			std::string method = original.substr(methodBegin, methodLength);
			original.replace(methodBegin, methodLength, "<span class='orange_code'>"+method+"</span>");
			start_pos = start_pos+methodLength + 32;
			continue;
		}

		end_pos = original.find_first_of("-+</>*=.;,()[]] ", start_pos+1);
		if(end_pos == std::string::npos)
		{
			start_pos++;
			continue;
		}

		start_pos++;
		length = end_pos-start_pos;
		originalWord = original.substr(start_pos, length);
		original.replace(start_pos, length, "<span class='green_code'>"+originalWord+"</span>");
		start_pos = end_pos + 25 + 7;
	}

	//Finding comments
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
}

void Keywords::highlightHTML(std::string &original)
{
	std::vector<std::string> keywords ={"<", ">"};
	std::vector<std::string> highlightedKeywords ={"&lt;", "&gt;"};
	for(int i=0;i<keywords.size();i++)
    {
        size_t start_pos=0;
        while((start_pos = original.find(keywords[i], start_pos)) != std::string::npos)
        {
            original.replace(start_pos, keywords[i].length(), highlightedKeywords[i]);
            start_pos +=highlightedKeywords[i].length();
        }
    }
		//original.replace(0, original.length(), "HTML highligting is not supported yet!");
		//Debug::warn("HTML highligting is not supported yet!");
}

void Keywords::highlight(std::string& path, std::string& code)
{
	std::string extension = getExtension(path);
	if(extension=="") return;

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
		if(path.find_last_of(".") == std::string::npos)
			return "";

		return path.substr(path.find_last_of(".")+1);
}
