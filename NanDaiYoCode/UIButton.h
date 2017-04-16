/*
A button that has idle, hovered and selected animations.
*/

#pragma once

#include "UIImage.h"

class UIButton : public UIImage
{
public:
	UIButton(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position);

	void handleEvent();
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

};
