#include "TextureManager.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "FontManager.h"
#include "CursorManager.h"

#include <iostream> // For testing purposes

int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");

	sf::Clock clock;
	float fFrameRate = 60.f;
	window.setFramerateLimit(static_cast<unsigned int>(fFrameRate));

	std::cout << TextureManager::getInstance().loadFromDirectory("Assets/Textures") << std::endl;
	std::cout << FontManager::getInstance().loadFromDirectory("Assets/Fonts") << std::endl;

	CursorManager::getInstance().setCursorVisible(window, false);
	CursorManager::getInstance().setCursor(UIImage("cursors", window, UIPosition(UIAnchor::TOP | UIAnchor::LEFT)));
	CursorManager::getInstance().getCursorImage().setTextureAnimation("Pointer");

	SceneManager::getInstance().clearAndAddScreen(new Screens::MainMenu(window));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			SceneManager::getInstance().handleEvents(event);
		}

		if (clock.getElapsedTime().asSeconds() > 1.f / fFrameRate)
		{
			float fFrameChunk = clock.restart().asSeconds();
			SceneManager::getInstance().update(fFrameChunk);
			CursorManager::getInstance().updateImage(fFrameChunk);
		}

		CursorManager::getInstance().updateMousePosition(window);

		window.clear(sf::Color(100, 100, 100));

		window.draw(SceneManager::getInstance());
		window.draw(CursorManager::getInstance());

		window.display();
	}

	return 0;
}