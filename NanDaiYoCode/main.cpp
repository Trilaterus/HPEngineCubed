#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SceneManager.h"
#include "MainMenuScreen.h"
#include "OptionsScreen.h"

#include <iostream> // For testing purposes

int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");
	//sf::RenderWindow* pWindow(&window);

	sf::Clock clock;
	float fFrameRate = 60.f;
	window.setFramerateLimit(static_cast<unsigned int>(fFrameRate));

	std::cout << TextureManager::getInstance().loadFromDirectory("Assets/Textures") << std::endl;
	SceneManager::getInstance().clearAndAddScreen(new MainMenuScreen(window));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			SceneManager::getInstance().handleEvents(event);
		}

		if (clock.getElapsedTime().asSeconds() > 1.f / fFrameRate) // Only draw per frame rate innit...
		{
			float fFrameChunk = clock.restart().asSeconds();
			SceneManager::getInstance().update(fFrameChunk);
		}

		window.clear(sf::Color(100, 100, 100));

		window.draw(SceneManager::getInstance());

		window.display();
	}

	return 0;
}