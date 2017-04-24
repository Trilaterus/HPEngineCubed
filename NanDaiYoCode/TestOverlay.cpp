#include "TestOverlay.h"

#include "SceneManager.h"
#include "UIImage.h"
#include "FadeColour.h"
#include "UIText.h"

#include "FontManager.h"

namespace Overlays
{
	Test::Test(const sf::RenderWindow& window)
		:
		Scene(window)
	{
		m_isOverlay = true;

		UIImage background = UIImage("background", m_Window, UIPosition());
		m_AllUI.push_back(std::make_shared<UIImage>(background));

		UIText centreAlign = UIText("Lin", m_Window, UIPosition(), UIText::Alignment::LEFT);
		centreAlign.setText("Normal colour, <c 123 213 123>different colour, <c 1 2 3 150>colour<br>transparency,</> prev colour,<br></> normal colour");
		m_AllUI.push_back(std::make_shared<UIText>(centreAlign));
	}

	void Test::handleEvents(const sf::Event& event)
	{
		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Down)
		{
			SceneManager::getInstance().popScene();
		}
	}

	void Test::update(float fFrameChunk)
	{
		Scene::update(fFrameChunk);
	}

	void Test::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		Scene::draw(target, states);

		sf::Vertex vline[] =
		{
			sf::Vertex(sf::Vector2f(target.getSize().x / 2.f, 0.f)),
			sf::Vertex(sf::Vector2f(target.getSize().x / 2.f, static_cast<float>(target.getSize().y)))
		};

		target.draw(vline, 2, sf::Lines);

		sf::Vertex hline[] =
		{
			sf::Vertex(sf::Vector2f(0.f, static_cast<float>(target.getSize().y / 2))),
			sf::Vertex(sf::Vector2f(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y / 2)))
		};

		target.draw(hline, 2, sf::Lines);

	}
}