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

		UIText centreAlign = UIText("Hemi", m_Window, UIPosition(), UIText::Alignment::CENTRE);
		centreAlign.setText("Normal colour, <c 123 213 123>different colour, <c 1 2 3 150>colour<br>transparency,</> prev colour,<br></>normal colour");
		m_AllUI.push_back(std::make_shared<UIText>(centreAlign));

		UIText topLeft = UIText("Lin", m_Window, UIPosition(UIAnchor::TOP | UIAnchor::LEFT), UIText::Alignment::RIGHT);
		topLeft.setText("This text is aligned properly even though one line<br>is way longer!");
		m_AllUI.push_back(std::make_shared<UIText>(topLeft));

		UIText botRight = UIText("M12 edited", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::RIGHT), UIText::Alignment::CENTRE);
		botRight.setText("<c 255 50 50>Even this is aligned!<br>And its colour is applied without an end tag");
		m_AllUI.push_back(std::make_shared<UIText>(botRight));

		UIText botLeft = UIText("Pixeltype", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::LEFT), UIText::Alignment::CENTRE);
		botLeft.setText("For some reason<br>this doesn't work?<br>Sad face :(");
		m_AllUI.push_back(std::make_shared<UIText>(botLeft));
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