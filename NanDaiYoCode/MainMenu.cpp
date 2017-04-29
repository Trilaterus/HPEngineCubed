#include "MainMenu.h"

#include "UIImage.h"
#include "Options.h"
#include "SceneManager.h"
#include "FadeColour.h"
#include "TestOverlay.h"
#include "UIButton.h"

namespace Screens
{
	MainMenu::MainMenu(const sf::RenderWindow& window)
		:
		Scene(window)
	{
		m_isOverlay = false; // Can't call this in the ':' bit of the constructor for some reason...

		UIImage logo = UIImage("logo_shadow", m_Window, UIPosition());
		UIImage logoLeft = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::LEFT));
		UIImage logoTopRight = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::RIGHT | UIAnchor::TOP));
		UIImage logoBotLeftCentre = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::RIGHT, UIAnchor::CENTRE));

		UIButton button = UIButton("blueSheet", m_Window, UIPosition());
		button.chooseProgrammedAnimation().setSinMovement(SinMovement(0.f, 0.f, 4.f, 2.f));

		m_AllUI.push_back(std::make_shared<UIImage>(logo));
		m_AllUI.push_back(std::make_shared<UIImage>(logoLeft));
		m_AllUI.push_back(std::make_shared<UIImage>(logoTopRight));
		m_AllUI.push_back(std::make_shared<UIImage>(logoBotLeftCentre));
		m_AllUI.push_back(std::make_shared<UIButton>(button));
	}

	void MainMenu::handleEvents(const sf::Event& event)
	{
		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Left)
		{
			SceneManager::getInstance().pushScreen(new Screens::Options(m_Window), new Transition::FadeColour());
		}

		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Up)
		{
			SceneManager::getInstance().pushOverlay(new Overlays::Test(m_Window));
		}
	}

	void MainMenu::update(float fFrameChunk)
	{
		Scene::update(fFrameChunk); // Calls update on all the UI
	}

	void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		Scene::draw(target, states); // Calls draw on all the UI
	}
}