/*
A button that has idle, hovered and selected animations.
*/

#pragma once

#include "UIImage.h"

class UIButton : public UIImage
{
public:
	enum UIButtonState
	{
		IDLE,
		HOVER,
		CLICK,
		RELEASE
	};

	UIButton(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position);

	void passEvent(const sf::Event& event, const sf::RenderWindow& window);
	UIButtonState GetState() const;

	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	UIButtonState m_currentState;

	bool mouseWithinBounds(const sf::RenderWindow& window);
	bool clickWithinBounds(const sf::RenderWindow& window);
	bool releasedWithinBounds(const sf::Event& event, const sf::RenderWindow& window);
};
