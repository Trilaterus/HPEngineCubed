/*
This class holds a set of UI objects and their handling
to create a single 'screen' in the game.
This normally consists of a background image, some
navigatable options with different functions and at
least one method of changing to another screen.
This class is abstract as for each specific screen
a subclass should be created.

NOTE: On hold.
*/

#pragma once

#include "Scene.h"

class MainMenuScreen : public Scene
{
public:
	MainMenuScreen(const sf::RenderWindow& window);

	void handleEvents(const sf::Event& event);
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

};