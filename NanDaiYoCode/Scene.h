/*
Scene is an abstract class to allow Screens and Overlays to
be stored in the same container. A scene is essentially a small
rectangle in which UI elements can be drawn and handled within.

A Screen is a full window sized display, only one can be drawn
at a time.

An Overlay is an up to full size display, multiple can be stacked
and drawn on top of each other (and on top of the current Screen)
*/

#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "UIObject.h"
#include <memory>

class Scene : public sf::Drawable
{
public:
	Scene(const sf::RenderWindow& window);

	virtual void handleEvents(const sf::Event& event) = 0;
	virtual void update(float fFrameChunk);	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::vector<std::shared_ptr<UIObject>> m_AllUI;
	bool m_isOverlay;
	const sf::RenderWindow& m_Window;

private:

};