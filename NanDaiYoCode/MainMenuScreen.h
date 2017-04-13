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