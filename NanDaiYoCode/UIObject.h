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

	virtual void handleEvent(/*sfEvent?*/) = 0;
	virtual void update(float fFrameChunk) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	UIPosition m_Position;

	//float m_fWidth; // Can't really figure this out at this abstract of a point
	//float m_fHeight; // so no point including it here

	// Also can't figure this out since we don't have the screen.
	// If needed could include a GetActualPos(sf::Window), need to
	// pass the window so that you can calculate it's actual position...
	// May actually need that for event handling? :S
	//float m_fXPos; // Actual position on the screen
	//float m_fYPos;

private:

};