#include "UIButton.h"

UIButton::UIButton(const std::string& sTextureName, const sf::RenderWindow& window, UIPosition position)
	:
	UIImage(sTextureName, window, position),
	m_currentState(UIButtonState::IDLE)
{

}

void UIButton::passEvent(const sf::Event & event, const sf::RenderWindow & window)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	const sf::FloatRect spriteBounds = m_Sprite.getGlobalBounds();

	if (mousePos.x >= spriteBounds.left &&
		mousePos.x <= spriteBounds.left + spriteBounds.width &&
		mousePos.y >= spriteBounds.top &&
		mousePos.y <= spriteBounds.top + spriteBounds.height)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_currentState = UIButtonState::CLICK;

		}
		else if (event.type == sf::Event::MouseButtonReleased &&
			event.key.code == sf::Mouse::Left)
		{
			m_currentState = UIButtonState::RELEASE;
		}
		else
		{
			m_currentState = UIButtonState::HOVER;
		}
	}
	else
	{
		m_currentState = UIButtonState::IDLE;
	}
}

void UIButton::setState(UIButtonState state)
{
	m_currentState = state;
}

UIButton::UIButtonState UIButton::getState() const
{
	return m_currentState;
}

bool UIButton::mouseWithinBounds(const sf::RenderWindow& window)
{
	const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	const sf::FloatRect spriteBounds = m_Sprite.getGlobalBounds();

	if (mousePos.x >= spriteBounds.left &&
		mousePos.x <= spriteBounds.left + spriteBounds.width &&
		mousePos.y >= spriteBounds.top &&
		mousePos.y <= spriteBounds.top + spriteBounds.height)
	{
		return true;
	}

	return false;
}

bool UIButton::clickWithinBounds(const sf::RenderWindow & window)
{
	if (this->mouseWithinBounds(window) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}

	return false;
}

bool UIButton::releasedWithinBounds(const sf::Event& event, const sf::RenderWindow& window)
{
	if (this->mouseWithinBounds(window) &&
		event.type == sf::Event::MouseButtonReleased &&
		event.key.code == sf::Mouse::Left)
	{
		return true;
	}

	return false;
}

void UIButton::update(float fFrameChunk)
{
	UIImage::update(fFrameChunk);
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIImage::draw(target, states);
}