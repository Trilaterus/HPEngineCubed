#include "OptionsScreen.h"

#include "UIImage.h"
#include "MainMenuScreen.h"
#include "SceneManager.h"

OptionsScreen::OptionsScreen(const sf::RenderWindow& window)
	:
	Scene(window)
{
	m_isOverlay = false; // Can't call this in the ':' bit of the constructor for some reason...

	UIImage scott = UIImage("newSpriteSheet", m_Window, UIPosition());
	scott.setTextureAnimationSpeed(8);
	m_AllUI.push_back(std::make_shared<UIImage>(scott));
}

void OptionsScreen::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Right)
	{
		//SceneManager::getInstance().pushScreen(new MainMenuScreen(m_Window), FadeColour());
		SceneManager::getInstance().popScreen(FadeColour());
	}
}

void OptionsScreen::update(float fFrameChunk)
{
	Scene::update(fFrameChunk); // Calls update on all the UI
}

void OptionsScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Scene::draw(target, states); // Calls draw on all the UI
}
