#include "TestOverlay.h"

#include "SceneManager.h"

TestOverlay::TestOverlay(const sf::RenderWindow& window)
	:
	Scene(window)
{
	m_isOverlay = true;
}

void TestOverlay::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Escape)
	{
		// Pop Overlay
	}
}

void TestOverlay::update(float fFrameChunk)
{
}

void TestOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
