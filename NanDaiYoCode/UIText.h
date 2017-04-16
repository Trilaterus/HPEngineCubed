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
	sf::Text m_Text;
};