/*
Used to display text on a Scene.
Inherits from UIObject.
*/

#pragma once

#include "UIObject.h"
#include "TextTagList.h"
#include <memory>

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
	std::vector<std::shared_ptr<TextTagMod>> m_TagStack;

	// Takes the current raw string and updates the vector of AllTexts (with effects and positioning)
	std::vector<sf::Text> parseRawString();

};