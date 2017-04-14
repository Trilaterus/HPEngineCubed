#include "TestOverlay.h"

#include "SceneManager.h"
#include "UIImage.h"
#include "FadeColour.h"

TestOverlay::TestOverlay(const sf::RenderWindow& window)
	:
	Scene(window)
{
	m_isOverlay = true;

	UIImage background = UIImage("background", m_Window, UIPosition());

	m_AllUI.push_back(std::make_shared<UIImage>(background));
}

void TestOverlay::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Down)
	{
		SceneManager::getInstance().popScene();
		//SceneManager::getInstance().popScreen(new FadeColour()); // Handled appropriately
	}
}

void TestOverlay::update(float fFrameChunk)
{
	Scene::update(fFrameChunk);
}

void TestOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Scene::draw(target, states);
}
