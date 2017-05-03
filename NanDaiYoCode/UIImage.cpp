#include "UIImage.h"
#include "TextureManager.h"

UIImage::UIImage(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position)
	:
	UIObject(position),
	m_TextureAnimator(&TextureManager::getInstance().getTexture(sTextureName))
{
	m_Sprite.setTexture(TextureManager::getInstance().getTexture(sTextureName));
	m_Sprite.setTextureRect(m_TextureAnimator.getCurrentTextureRect());

	UIObject::setOrigin(&m_Sprite, m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);

	UIObject::setScreenAnchor(&m_Sprite, target);
	UIObject::setOffsetPosition(&m_Sprite, position.m_fXOffset, position.m_fYOffset);
}

void UIImage::setTextureAnimation(const std::string & sAnimationName)
{
	m_TextureAnimator.changeAnimation(sAnimationName);
}

void UIImage::setTextureAnimationSpeed(int iFrameSpeed)
{
	m_TextureAnimator.setFrameSpeed(iFrameSpeed);
}

UIProgrammedAnimation& UIImage::chooseProgrammedAnimation()
{
	return m_ProgrammedAnimator;
}

void UIImage::setUIPosition(const UIPosition& position, const sf::RenderWindow& window)
{
	UIObject::setOrigin(&m_Sprite, m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);

	UIObject::setScreenAnchor(&m_Sprite, window);
	UIObject::setOffsetPosition(&m_Sprite, position.m_fXOffset, position.m_fYOffset);
}

void UIImage::update(float fFrameChunk)
{
	m_TextureAnimator.updateFrameByTime(fFrameChunk);
	m_Sprite.setTextureRect(m_TextureAnimator.getCurrentTextureRect());
	setOrigin(&m_Sprite, m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height); // Needed as it recalculates based on current texture rect

	m_ProgrammedAnimator.update(fFrameChunk);
	m_Sprite.setPosition(m_vScreenAnchorOGPos.x + m_ProgrammedAnimator.getOffsets().x, m_vScreenAnchorOGPos.y + m_ProgrammedAnimator.getOffsets().y);
}

void UIImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}