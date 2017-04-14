#include "OptionsScreen.h"

#include "UIImage.h"
#include "MainMenuScreen.h"
#include "SceneManager.h"
#include "FadeColour.h"
#include "TestOverlay.h"

OptionsScreen::OptionsScreen(const sf::RenderWindow& window)
	:
	Scene(window)
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
}

void OptionsScreen::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Right)
	{
		SceneManager::getInstance().popScreen(new FadeColour());
	}

	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Up)
	{
		SceneManager::getInstance().pushOverlay(new TestOverlay(m_Window));
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
