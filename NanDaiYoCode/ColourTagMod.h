/*
This class handles tags <c 255 100 100>such as this one!</>
The purpose of the tag is to change the colour of the text
that it contains.
*/

#pragma once

#include "TextTagMod.h"

namespace TextTag
{
	class Colour : public TextTagMod
	{
	public:
		Colour();

		bool validate(const std::vector<std::string>& vTagContents);
		void modifyText(sf::Text& sfText);

	private:
		sf::Color m_sfColour;

		void setup(const std::vector<std::string>& vTagContents);
	};
}