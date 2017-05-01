#include "Options.h"

#include "UIImage.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "FadeColour.h"
#include "TestOverlay.h"

namespace Screens
{
	Options::Options(const sf::RenderWindow& window)
		:
		Scene(window),
		m_pButton(new UIButton("blueSheet", m_Window, UIPosition(UIAnchor::BOT | UIAnchor::RIGHT, -10.f, -10.f)))
	{
		m_isOverlay = false; // Can't call this in the ':' bit of the constructor for some reason...

		UIImage scottLeft = UIImage("newSpriteSheet", m_Window, UIPosition(UIAnchor::LEFT, 100.f));
		scottLeft.setTextureAnimationSpeed(8);

		UIImage scott = UIImage("newSpriteSheet", m_Window, UIPosition());
		scott.setTextureAnimationSpeed(8);
		scott.setTextureAnimation("Run");

		UIImage scottRight = UIImage("newSpriteSheet", m_Window, UIPosition(UIAnchor::RIGHT, -100.f));
		scottRight.setTextureAnimationSpeed(8);
		scottRight.setTextureAnimation("Run");
		scottRight.chooseProgrammedAnimation().setSinMovement(SinMovement(0.f, 0.f, 30.f, 1.f));
		scottRight.chooseProgrammedAnimation().setShakeMovement(ShakeMovement(10, 8.f));

		m_AllUI.push_back(std::make_shared<UIImage>(scottLeft));
		m_AllUI.push_back(std::make_shared<UIImage>(scott));
		m_AllUI.push_back(std::make_shared<UIImage>(scottRight));
		m_AllUI.push_back(m_pButton);
	}

	void Options::handleEvents(const sf::Event& event)
	{
		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Up)
		{
			SceneManager::getInstance().pushOverlay(new Overlays::Test(m_Window));
		}

		m_pButton->passEvent(event, m_Window);
	}

	void Options::update(float fFrameChunk)
	{
		this->handleMainMenuButton();

		Scene::update(fFrameChunk); // Calls update on all the UI
	}

	void Options::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		Scene::draw(target, states); // Calls draw on all the UI
	}

	void Options::handleMainMenuButton()
	{
		switch (m_pButton->GetState())
		{
		case UIButton::RELEASE:
			m_pButton->setTextureAnimation("Idle");
			SceneManager::getInstance().pushScreen(new Screens::MainMenu(m_Window), new Transition::FadeColour());
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
	}
}