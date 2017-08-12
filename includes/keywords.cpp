#include "keywords.h"

void Keywords::highlightCSharp()
{
	std::string originalWord = "";
	std::size_t start_pos = 0;
	std::size_t end_pos = 0;
	std::size_t length = 0;

	//Replace less than character
	start_pos = 0;
	while((start_pos = original.find('<', start_pos)) != std::string::npos)
	{
		if(original.substr(start_pos+1, 4) == "span" || original.substr(start_pos+1, 5) == "/span")
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "&lt;";
		original.replace(start_pos, 1, highlighted);
		start_pos += highlighted.length();
	}

	//Replace greater than character
	start_pos = 0;
	while((start_pos = original.find('>', start_pos)) != std::string::npos)
	{
		if(original.substr(start_pos-4, 4) == "span" || original.substr(start_pos-5, 5) == "/span")
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "&gt;";
		original.replace(start_pos, 1, highlighted);
		start_pos += highlighted.length();
	}

	//Replace if keyword
	start_pos = 0;
	while((start_pos = original.find("if", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 2] != '(' && original[start_pos + 3] != '(')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos - 1] != ' ' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>if</span>";
		original.replace(start_pos, 2, highlighted);
		start_pos += highlighted.length();
	}

	//Replace else keyword
	start_pos = 0;
	while((start_pos = original.find("else", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 4] != ' ' && original[start_pos + 4] != '{' && original[start_pos + 4] != '\n')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos - 1] != ' ' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>else</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace while keyword
	start_pos = 0;
	while((start_pos = original.find("while", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 5] != '(' && original[start_pos + 6] != '(')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos - 1] != ' ' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>while</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace using keyword
	start_pos = 0;
	while((start_pos = original.find("using", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 5] != ' ' || !isupper(original[start_pos + 6]))
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>using</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

  //Replace int keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("int", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 3))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 3);
		std::string highlighted = "<span class='pink_code'>int</span>";
		original.replace(start_pos, 3, highlighted);
		start_pos += highlighted.length();
	}

	//Replace bool keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("bool", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 4))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 4);
		std::string highlighted = "<span class='pink_code'>bool</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace float keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("float", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 5))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 5);
		std::string highlighted = "<span class='pink_code'>float</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace string keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("string", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 6))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 6);
		std::string highlighted = "<span class='pink_code'>string</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Replace IEnumerator keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("IEnumerator", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 11))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 11);
		std::string highlighted = "<span class='blue_code'>IEnumerator</span>";
		original.replace(start_pos, 11, highlighted);
		start_pos += highlighted.length();
	}

	//Replace double keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("double", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 6))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 6);
		std::string highlighted = "<span class='pink_code'>double</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Replace char keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("char", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 4))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 4);
		std::string highlighted = "<span class='pink_code'>char</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace void keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("void", start_pos)) != std::string::npos)
	{
		if(!validType(start_pos, 4))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 4);
		std::string highlighted = "<span class='pink_code'>void</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}
	//Replace enum keywords
	start_pos = 0;
	while ((start_pos = original.find("enum", start_pos)) != std::string::npos)
	{
		if(original[start_pos - 1] != ' ' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos + 4] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>enum</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace var keywords
	start_pos = 0;
	while ((start_pos = original.find("var", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos-1] != '(' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+3] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>var</span>";
		original.replace(start_pos, 3, highlighted);
		start_pos += highlighted.length();
	}

	//Replace value keywords
	start_pos = 0;
	while ((start_pos = original.find("value", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos-1] != '(' && original[start_pos - 1] != '{' && original[start_pos - 1] != '<' && original[start_pos - 2] != '<' && original[start_pos - 1] != '>' && original[start_pos - 2] != '>' && original[start_pos - 1] != '=' && original[start_pos - 2] != '=')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos + 5] != ';' && original[start_pos + 5] != '=' && original[start_pos + 6] != '=' && original[start_pos + 5] != '<' && original[start_pos + 6] != '<' && original[start_pos + 5] != '>' && original[start_pos + 6] != '>')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>value</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace private keyword
	start_pos = 0;
	while((start_pos = original.find("private", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 7] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>private</span>";
		original.replace(start_pos, 7, highlighted);
		start_pos += highlighted.length();
	}

	//Replace public keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("public", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 6] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>public</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Replace protected keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("protected", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 9] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>protected</span>";
		original.replace(start_pos, 9, highlighted);
		start_pos += highlighted.length();
	}

	//Replace sealed keyword and methods after it
	start_pos = 0;
	while((start_pos = original.find("sealed", start_pos)) != std::string::npos)
	{
		if(original[start_pos + 6] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>sealed</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Replace this keyword
	start_pos = 0;
	while((start_pos = original.find("this", start_pos)) != std::string::npos)
	{
		if(original[start_pos+4] != ';' && original[start_pos+4] != '.' && original[start_pos-1] != ' ' && original[start_pos-1] != '=')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='purple_code'>this</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace get keyword
	start_pos = 0;
	while((start_pos = original.find("get", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != '{' && original[start_pos-2] != '{' && original[start_pos-1] != '\n' && original[start_pos+3] != '{' && original[start_pos-3] != '\n')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>get</span>";
		original.replace(start_pos, 3, highlighted);
		start_pos += highlighted.length();
	}

	//Replace set keyword
	start_pos = 0;
	while((start_pos = original.find("set", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != '{' && original[start_pos-2] != '{' && original[start_pos-1] != '\n' && original[start_pos+3] != '{' && original[start_pos-3] != '\n')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>set</span>";
		original.replace(start_pos, 3, highlighted);
		start_pos += highlighted.length();
	}

	//Replace null keywords
	start_pos = 0;
	while ((start_pos = original.find("null", start_pos)) != std::string::npos)
	{
		if(original[start_pos+4] != ';' && original[start_pos+4] != ' ' && original[start_pos+4] != ')')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos-1] != ' ' && original[start_pos-1] != '=' && original[start_pos-2] != '=')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>null</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace new keywords
	start_pos = 0;
	while ((start_pos = original.find("new", start_pos)) != std::string::npos)
	{
		if(original[start_pos+3] != ' ')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos-1] != ' ' && original[start_pos-1] != '=' && original[start_pos-2] != '=')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>new</span>";
		original.replace(start_pos, 3, highlighted);
		start_pos += highlighted.length();
	}

	//Replace new keywords
	start_pos = 0;
	while ((start_pos = original.find("yield", start_pos)) != std::string::npos)
	{
		if(original[start_pos+5] != ' ')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos-1] != ' ' && original[start_pos-1] != '\t')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>yield</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace class keywords
	start_pos = 0;
	while ((start_pos = original.find("class", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos+5] != ' ')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+5] == '=' || original[start_pos+6] == '=')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>class</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace return keyword
	start_pos = 0;
	while((start_pos = original.find("return", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos - 1] != '\t' && original[start_pos+6] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>return</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Replace true keywords
	start_pos = 0;
	while ((start_pos = original.find("true", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos-1] != '=' && original[start_pos-2] != '=' && original[start_pos-1] != '(' && original[start_pos-2] != '(')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+4] != ' ' && original[start_pos+4] != ';' && original[start_pos+4] != ')')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='purple_code'>true</span>";
		original.replace(start_pos, 4, highlighted);
		start_pos += highlighted.length();
	}

	//Replace false keywords
	start_pos = 0;
	while ((start_pos = original.find("false", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' && original[start_pos-1] != '=' && original[start_pos-2] != '=' && original[start_pos-1] != '(' && original[start_pos-2] != '(')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+5] != ' ' && original[start_pos+5] != ';' && original[start_pos+5] != ')')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='purple_code'>false</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace const keywords
	start_pos = 0;
	while ((start_pos = original.find("const", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' &&  original[start_pos-1] != '(' && original[start_pos-2] != '(' && original[start_pos - 1] != '\t')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+5] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>const</span>";
		original.replace(start_pos, 5, highlighted);
		start_pos += highlighted.length();
	}

	//Replace static keywords
	start_pos = 0;
	while ((start_pos = original.find("static", start_pos)) != std::string::npos)
	{
		if(original[start_pos-1] != ' ' &&  original[start_pos-1] != '(' && original[start_pos-2] != '(')
		{
			start_pos++;
			continue;
		}

		if(original[start_pos+6] != ' ')
		{
			start_pos++;
			continue;
		}

		std::string highlighted = "<span class='pink_code'>static</span>";
		original.replace(start_pos, 6, highlighted);
		start_pos += highlighted.length();
	}

	//Finding strings
	start_pos = 0;
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
    start_pos = end_pos + newWord.length();
	}

	//Looks for words starting with a cap
	for(int i = 0; i < original.size(); i++)
	{
		start_pos = i;
		if(!isupper(original[start_pos]))
		continue;
		if(!isspace(original[start_pos-1]) && original.substr(start_pos-1, 1) != ";" && original.substr(start_pos-1, 1) != "[" && original.substr(start_pos-1, 1) != "(")
			continue;

		end_pos = original.find_first_of("[]{}()<>\n;&. ", start_pos + 1);
		length = end_pos - start_pos;
		originalWord = original.substr(start_pos, length);
		original.replace(start_pos, length, "<span class='blue_code'>"+originalWord+"</span>");
	}

	//Find words after a period
	start_pos = 0;
	while((start_pos = original.find(".", start_pos)) != std::string::npos)
	{
		if(isdigit(original[start_pos + 1]) && isdigit(original[start_pos - 1]))
		{
			start_pos++;
			continue;
		}

		highlightCSharpMethod(start_pos, 1);

		end_pos = original.find_first_of("-+</>*=.;,()[]]& ", start_pos+1);
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

bool Keywords::validType(size_t pos, int typeLength)
{
	if(original[pos - 1] != ' '  && original[pos - 1] != '{' && original[pos - 1] != '(' && original[pos - 1] != ';')
		return false;
	else if(original[pos + typeLength] != ' ' && original[pos + typeLength] != '[' && original[pos + typeLength] != '&')
		return false;
	else
		return true;
}

void Keywords::highlightCSharpMethod(size_t pos, int typeLength)
{
	size_t methodBegin = pos + typeLength;
	size_t methodEnd = original.find_first_of("(", methodBegin);
	size_t interuption = original.find_first_of("=\n{})&;", methodBegin);
	if(methodEnd != std::string::npos && methodEnd < interuption)
	{
		size_t methodLength = methodEnd - methodBegin;
		std::string method = original.substr(methodBegin, methodLength);
		original.replace(methodBegin, methodLength, "<span class='orange_code'>"+method+"</span>");
	}
}

void Keywords::highlightHTML()
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

std::string Keywords::highlight(std::string path, std::string &code)
{
	std::string extension = getExtension(path);
	if(extension=="") return original;

	original = code;
	if(extension == "cs")
	{
		highlightCSharp();
		return original;
	}

	if(extension == "html" || extension == "php")
	{
		highlightHTML();
		return original;
	}
	return original;
}

std::string Keywords::getExtension(const std::string path)
{
		if(path.find_last_of(".") == std::string::npos)
			return "";

		return path.substr(path.find_last_of(".")+1);
}
