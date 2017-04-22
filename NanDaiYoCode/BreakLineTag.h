/*
This class makes the following text draw on a new line using <br>
The main handling for this class happens in UIText, since that's
where the position information for all texts are.
*/

#pragma once

#include "TextTagMod.h"

namespace TextTag
{
	class BreakLine : public TextTagMod
	{
	public:
		BreakLine();

		bool validate(const std::vector<std::string>& vTagContents);
		void modifyText(sf::Text& sfText);
	};
}