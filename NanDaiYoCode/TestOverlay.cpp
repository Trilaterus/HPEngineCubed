#include "TestOverlay.h"

#include "SceneManager.h"
#include "UIImage.h"
#include "FadeColour.h"
#include "UIText.h"

namespace Overlays
{
	Test::Test(const sf::RenderWindow& window)
		:
		Scene(window)
	{
		m_isOverlay = true;

		UIImage background = UIImage("background", m_Window, UIPosition());
		m_AllUI.push_back(std::make_shared<UIImage>(background));

		UIText centreAlign = UIText("Hemi", m_Window, UIPosition(), UIText::Alignment::CENTRE);
		centreAlign.setText("Normal colour, <c 123 213 123>different colour, <c 1 2 3 150>colour<br>transparency,</> prev colour,</> normal colour");
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
	}
}