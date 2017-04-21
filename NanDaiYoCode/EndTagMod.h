/*
This class pops off a tag from the stack. It should look like </>
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