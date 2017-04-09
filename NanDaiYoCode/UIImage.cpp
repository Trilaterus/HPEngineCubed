#include "UIImage.h"
#include "TextureManager.h"

UIImage::UIImage(const std::string& sTextureName)
	:
	UIObject(),
	m_vScreenAnchorOGPos(0, 0),
	m_TextureAnimator(&TextureManager::getInstance().getTexture(sTextureName))
{
	m_Sprite.setTexture(TextureManager::getInstance().getTexture(sTextureName));
	m_Sprite.setTextureRect(m_TextureAnimator.getCurrentTextureRect());

	this->setOrigin(); // Still need this as default SFML center is top left, whereas we want center center
}

UIImage::UIImage(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position)
	:
	UIObject(position),
	m_TextureAnimator(&TextureManager::getInstance().getTexture(sTextureName))
{
	m_Sprite.setTexture(TextureManager::getInstance().getTexture(sTextureName));
	m_Sprite.setTextureRect(m_TextureAnimator.getCurrentTextureRect());

	this->setOrigin();

	this->setScreenAnchor(target);
	this->setOffsetPosition(position.m_fXOffset, position.m_fYOffset);
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

void UIImage::setOrigin()
{
	// If having issues with texture rect/position being off try understanding this thread
	// https://en.sfml-dev.org/forums/index.php?topic=18049.0

	float fWidth = static_cast<float>(m_Sprite.getTextureRect().width);
	float fHeight = static_cast<float>(m_Sprite.getTextureRect().height);

	if (m_Position.m_iOriginAnchor & 2)
	{
		m_Sprite.setOrigin(fWidth, m_Sprite.getOrigin().y);
	}
	else if (!(m_Position.m_iOriginAnchor & 1))
	{
		m_Sprite.setOrigin(fWidth / 2.f, m_Sprite.getOrigin().y);
	}

	if (m_Position.m_iOriginAnchor & 8)
	{
		m_Sprite.setOrigin(m_Sprite.getOrigin().x, fHeight);
	}
	else if (!(m_Position.m_iOriginAnchor & 4))
	{
		m_Sprite.setOrigin(m_Sprite.getOrigin().x, fHeight / 2.f);
	}

	m_Sprite.setOrigin(std::roundf(m_Sprite.getOrigin().x), std::roundf(m_Sprite.getOrigin().y));
}

void UIImage::setScreenAnchor(const sf::RenderTarget& target)
{
	float fWidth = static_cast<float>(target.getSize().x);
	float fHeight = static_cast<float>(target.getSize().y);

	if (m_Position.m_iScreenAnchor & 2)
	{
		m_Sprite.setPosition(fWidth, m_Sprite.getPosition().y);
	}
	else if (!(m_Position.m_iScreenAnchor & 1))
	{
		m_Sprite.setPosition(fWidth / 2.f, m_Sprite.getPosition().y);
	}

	if (m_Position.m_iScreenAnchor & 8)
	{
		m_Sprite.setPosition(m_Sprite.getPosition().x, fHeight);
	}
	else if(!(m_Position.m_iScreenAnchor & 4))
	{
		m_Sprite.setPosition(m_Sprite.getPosition().x, fHeight / 2.f);
	}

	m_Sprite.setPosition(roundf(m_Sprite.getPosition().x), roundf(m_Sprite.getPosition().y));

	m_vScreenAnchorOGPos = m_Sprite.getPosition();
}

void UIImage::setOffsetPosition(float fXOffset, float fYOffset)
{
	m_Sprite.move(fXOffset, fYOffset); // Maybe change to setPosition (similar to programmed animation update?)

	m_vScreenAnchorOGPos = m_Sprite.getPosition();
}

void UIImage::handleEvent()
{

}

void UIImage::update(float fFrameChunk)
{
	m_TextureAnimator.updateFrameByTime(fFrameChunk);
	m_Sprite.setTextureRect(m_TextureAnimator.getCurrentTextureRect());
	setOrigin(); // Needed as it recalculates based on current texture rect

	m_ProgrammedAnimator.update(fFrameChunk);
	m_Sprite.setPosition(m_vScreenAnchorOGPos.x + m_ProgrammedAnimator.getOffsets().x, m_vScreenAnchorOGPos.y + m_ProgrammedAnimator.getOffsets().y);
}

void UIImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}