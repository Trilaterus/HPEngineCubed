/*
This class pops off a tag from the stack. It should look like </>.
The main handling for this class happens in UIText, since that's
where the stack of tags is.
*/

#pragma once

#include "TextTagMod.h"

namespace TextTag
{
	class End : public TextTagMod
	{
	public:
		End();

		bool validate(const std::vector<std::string>& vTagContents);
		void modifyText(sf::Text& sfText);
	};
}