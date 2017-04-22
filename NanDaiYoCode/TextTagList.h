/*
This function for the TextTag namespace is to return a pointer
to the appropriate text tag based on the function character.
*/

#pragma once

#include "ColourTagMod.h"
#include "EndTagMod.h"
#include "BreakLineTag.h"

namespace TextTag
{
	inline TextTagMod* tagList(std::string sCommand)
	{
		if (sCommand == "c")
		{
			return new TextTag::Colour();
		}
		else if (sCommand == "/")
		{
			return new TextTag::End();
		}
		else if (sCommand == "br")
		{
			return new TextTag::BreakLine();
		}

		return nullptr;
	}
}