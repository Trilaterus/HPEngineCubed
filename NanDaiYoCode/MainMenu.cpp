#include "MainMenu.h"

#include "UIImage.h"
#include "Options.h"
#include "SceneManager.h"
#include "FadeColour.h"
#include "TestOverlay.h"
#include "CursorManager.h"
#include "AudioManager.h"

namespace Screens
{
	MainMenu::MainMenu(const sf::RenderWindow& window)
		:
		Scene(window),
		m_pButton(new UIButton("blueSheet", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::LEFT, 10.f, -10.f))),
		m_pButtonText(new UIText("Hemi", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::LEFT, UIAnchor::CENTRE, 100.f, -40.f), UIText::Alignment::CENTRE))
	{
		m_isOverlay = false; // Can't call this in the ':' bit of the constructor for some reason...

		UIImage logo = UIImage("logo_shadow", m_Window, UIPosition());
		UIImage logoLeft = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::LEFT));
		UIImage logoTopRight = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::RIGHT | UIAnchor::TOP));
		UIImage logoBotLeftCentre = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::RIGHT, UIAnchor::CENTRE));
		UIImage logoBotCentre = UIImage("logo_shadow", m_Window, UIPosition(UIAnchor::BOT));
		logoBotCentre.setOrigin(UIAnchor::CENTRE, m_Window);
		logoBotCentre.setScreenAnchor(UIAnchor::TOP | UIAnchor::LEFT, m_Window);

		m_pButtonText->setText("Options");

		m_AllUI.push_back(std::make_shared<UIImage>(logo));
		m_AllUI.push_back(std::make_shared<UIImage>(logoLeft));
		m_AllUI.push_back(std::make_shared<UIImage>(logoTopRight));
		m_AllUI.push_back(std::make_shared<UIImage>(logoBotLeftCentre));
		m_AllUI.push_back(std::make_shared<UIImage>(logoBotCentre));
		m_AllUI.push_back(m_pButton);
		m_AllUI.push_back(m_pButtonText);
	}

	void MainMenu::handleEvents(const sf::Event& event)
	{
		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Up)
		{
			SceneManager::getInstance().pushOverlay(new Overlays::Test(m_Window));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//AudioManager::getInstance().toggleMusic("Rain", true);
		}

		m_pButton->passEvent(event, m_Window);
	}

	void MainMenu::update(float fFrameChunk)
	{
		this->handleOptionsButton();

		Scene::update(fFrameChunk); // Calls update on all the UI
	}

	void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		Scene::draw(target, states); // Calls draw on all the UI
	}

	void MainMenu::handleOptionsButton()
	{
		switch (m_pButton->getState())
		{
		case UIButton::RELEASE:
			m_pButton->setTextureAnimation("Idle");
			SceneManager::getInstance().pushScreen(new Screens::Options(m_Window), new Transition::FadeColour());
			m_pButton->setState(UIButton::IDLE);
			break;

		case UIButton::CLICK:
			m_pButton->setTextureAnimation("Click");
			break;

		case UIButton::HOVER:
			m_pButton->setTextureAnimation("Hover");
			break;

		case UIButton::IDLE:
		default:
			m_pButton->setTextureAnimation("Idle");
			break;
		}

		if (m_pButton->getState() == UIButton::CLICK)
		{
			m_pButtonText->setOffsetPosition(100.f, -36.f, m_Window);
		}
		else
		{
			m_pButtonText->setOffsetPosition(100.f, -40.f, m_Window);
		}

		if (m_pButton->getState() != UIButton::IDLE)
		{
			CursorManager::getInstance().getCursorImage().setTextureAnimation("Hand");
		}
		else
		{
			CursorManager::getInstance().getCursorImage().setTextureAnimation("Pointer");
		}
	}
}