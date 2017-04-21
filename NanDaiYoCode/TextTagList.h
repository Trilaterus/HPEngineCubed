/*
This function for the TextTag namespace is to return a pointer
to the appropriate text tag based on the function character.
*/

#pragma once

#include "ColourTagMod.h"
#include "EndTagMod.h"

namespace TextTag
{
	inline TextTagMod* tagList(char c)
	{
		if (c == 'c')
		{
			return new TextTag::Colour();
		}
		if (c == '/')
		{
			return new TextTag::End();
		}

		return nullptr;
	}
}