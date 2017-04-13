/*
Test overlay with no real purpose other
than to demonstrate an overlay working.
*/

#pragma once

#include "Scene.h"

class TestOverlay : public Scene
{
public:
	TestOverlay(const sf::RenderWindow& window);

	void handleEvents(const sf::Event& event);
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

};