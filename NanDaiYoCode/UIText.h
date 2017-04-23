/*
Used to display text on a Scene.
Inherits from UIObject.
This working code in this class is super fragile,
read through thoroughly before making any changes!
*/

#pragma once

#include "UIObject.h"
#include "TextTagList.h"
#include <memory>

class UIText : public UIObject
{
public:
	enum Alignment
	{
		LEFT,
		CENTRE,
		RIGHT
	};

	UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position, Alignment align = Alignment::LEFT);

	void setText(const std::string& sNewText);

	void handleEvent();
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string m_sRawString;
	std::string m_sFontName;
	std::vector<std::vector<sf::Text>> m_AllTexts; // A vector of vectors of sf::Texts
	std::vector<std::shared_ptr<TextTagMod>> m_TagStack;
	Alignment m_Alignment;

	std::vector<std::vector<sf::Text>> parseRawString(); // Takes the current raw string and updates the vector of AllTexts (with effects and positioning)
	void alignTextVector();
};