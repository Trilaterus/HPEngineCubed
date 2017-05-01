/*
An abstract class for all elements of UI. Provides basic
functionality all UI should adhere to.
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "UIPosition.h"
// Don't include TextureManager because not all UI objects need it. (e.g UIList? [aka UIOption])

class UIObject : public sf::Drawable
{
public:
	UIObject(UIPosition position = UIPosition())
		:
		m_Position(position)
	{
	}

	virtual void update(float fFrameChunk) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	UIPosition m_Position;
	sf::Vector2f m_vScreenAnchorOGPos; // May not be accurate, ensure to update with setScreenAnchor() and/or setOffsetPosition()

	void setOrigin(sf::Transformable* sfObject, float fWidth, float fHeight);
	void setScreenAnchor(sf::Transformable* sfObject, const sf::RenderTarget& target);
	void setOffsetPosition(sf::Transformable* sfObject, float fXOffset, float fYOffset);

private:
};