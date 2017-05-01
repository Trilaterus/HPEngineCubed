#include "UIButton.h"

UIButton::UIButton(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position)
	:
	UIImage(sTextureName, target, position)
{

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

void UIButton::update(float fFrameChunk)
{
	UIImage::update(fFrameChunk);
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIImage::draw(target, states);
}