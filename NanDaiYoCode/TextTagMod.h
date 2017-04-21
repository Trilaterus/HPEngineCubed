/*
This is an abstract class to help contain a collection
of tag information. A text tag is <b>something like this</>
and the information that gets stored is how it interacts
with the drawing of the sf::Text.
*/

#pragma once

#include "SFML\Graphics\Text.hpp"

class TextTagMod
{
public:
	TextTagMod() {};

	virtual bool validate(const std::vector<std::string>& vTagContents) = 0;
	virtual void modifyText(sf::Text& sfText) = 0;
};