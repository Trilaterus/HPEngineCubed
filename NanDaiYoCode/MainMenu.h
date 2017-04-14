#pragma once

#include "Scene.h"

namespace Screens
{
	class MainMenu : public Scene
	{
	public:
		MainMenu(const sf::RenderWindow& window);

		void handleEvents(const sf::Event& event);
		void update(float fFrameChunk);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

	};
}