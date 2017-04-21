/*
A namespace of functions to validate if strings can
be converted to various types.
*/

#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <sstream>

namespace StringHelper
{
	inline bool CanStringToInt(const std::string& sText)
	{
		// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c	
		std::string::const_iterator it = sText.begin();
		while (it != sText.end() && std::isdigit(*it)) ++it;
		return !sText.empty() && it == sText.end();
	}

	inline std::vector<std::string> SplitString(const std::string& sText, const char sDelimiter = ' ')
	{
		std::vector<std::string> AllStrings;

		// http://stackoverflow.com/a/5167799
		std::istringstream stream(sText);
		std::string string;
		while (std::getline(stream, string, sDelimiter))
		{
			AllStrings.push_back(string);
		}

		return AllStrings;
	}
}