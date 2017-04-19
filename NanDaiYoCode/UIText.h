/*
Used to display text on a Scene.
Inherits from UIObject.
*/

#pragma once

#include "UIObject.h"

class UIText : public UIObject
{
public:
	UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position);

	void setText(const std::string& sNewText);

	void handleEvent();
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::string m_sRawString;
	std::string m_sFontName;
	std::vector<sf::Text> m_AllTexts;

	const std::string m_sColourTag;

	std::vector<sf::Text> parseRawString();
	bool validateTagContents(const std::vector<std::string>& vTagContents);
	void updateTextModifier(sf::Text& modifier, const std::vector<std::string>& vTagContents);
};