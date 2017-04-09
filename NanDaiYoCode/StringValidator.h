/*
A namespace of functions to validate if strings can
be converted to various types.
*/

#pragma once

#include <string>
#include <cctype>

namespace StringValidator
{
	bool CanStringToInt(const std::string& sText)
	{
		// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
		
		std::string::const_iterator it = sText.begin();
		while (it != sText.end() && std::isdigit(*it)) ++it;
		return !sText.empty() && it == sText.end();
	}
}