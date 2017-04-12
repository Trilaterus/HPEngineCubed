#include "MainMenuScreen.h"

#include "UIImage.h"
#include "OptionsScreen.h"
#include "SceneManager.h"

MainMenuScreen::MainMenuScreen(const sf::RenderWindow& window)
	:
	Scene(window)
{
	m_isOverlay = false; // Can't call this in the ':' bit of the constructor for some reason...

	UIImage logo = UIImage("logo_shadow", m_Window, UIPosition());
	UIImage logoLeft = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::LEFT));
	UIImage logoTopRight = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::RIGHT | UIAnchor::TOP));
	UIImage logoBotLeftCentre = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::RIGHT, UIAnchor::CENTRE));

	m_AllUI.push_back(std::make_shared<UIImage>(logo));
	m_AllUI.push_back(std::make_shared<UIImage>(logoLeft));
	m_AllUI.push_back(std::make_shared<UIImage>(logoTopRight));
	m_AllUI.push_back(std::make_shared<UIImage>(logoBotLeftCentre));
}

void MainMenuScreen::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Left)
	{
		SceneManager::getInstance().pushScreen(new OptionsScreen(m_Window), FadeColour());
	}
}

void MainMenuScreen::update(float fFrameChunk)
{
	Scene::update(fFrameChunk); // Calls update on all the UI
}

void MainMenuScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Scene::draw(target, states); // Calls draw on all the UI
}
