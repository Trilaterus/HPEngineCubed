#include "UIObject.h"

UIPosition UIObject::getUIPosition() const
{
	return m_Position;
}

void UIObject::setOrigin(UIAnchor anchor, const sf::RenderWindow & window)
{
	m_Position.m_iOriginAnchor = anchor;

	this->setUIPosition(m_Position, window);
}

void UIObject::setScreenAnchor(UIAnchor anchor, const sf::RenderWindow & window)
{
	m_Position.m_iScreenAnchor = anchor;

	this->setUIPosition(m_Position, window);
}

void UIObject::setOffsetPosition(float fXOffset, float fYOffset, const sf::RenderWindow& window)
{
	m_Position.m_fXOffset = fXOffset;
	m_Position.m_fYOffset = fYOffset;

	this->setUIPosition(m_Position, window);
}

void UIObject::setOrigin(sf::Transformable* sfObject, float fWidth, float fHeight)
{
	// If having issues with texture rect/position being off try understanding this thread
	// https://en.sfml-dev.org/forums/index.php?topic=18049.0

	if (m_Position.m_iOriginAnchor & 2) // If RIGHT
	{
		sfObject->setOrigin(fWidth, sfObject->getOrigin().y);
	}
	else if (!(m_Position.m_iOriginAnchor & 1)) // If !LEFT (so CENTRE)
	{
		sfObject->setOrigin(fWidth / 2.f, sfObject->getOrigin().y);
	}
	else // If LEFT
	{
		sfObject->setOrigin(0.f, sfObject->getOrigin().y);
	}

	if (m_Position.m_iOriginAnchor & 8) // If BOT
	{
		sfObject->setOrigin(sfObject->getOrigin().x, fHeight);
	}
	else if (!(m_Position.m_iOriginAnchor & 4)) // If !TOP (so CENTRE)
	{
		sfObject->setOrigin(sfObject->getOrigin().x, fHeight / 2.f);
	}
	else
	{
		sfObject->setOrigin(sfObject->getOrigin().x, 0.f);
	}

	sfObject->setOrigin(std::roundf(sfObject->getOrigin().x), std::roundf(sfObject->getOrigin().y));
}

void UIObject::setScreenAnchor(sf::Transformable* sfObject, const sf::RenderWindow& window)
{
	float fWidth = static_cast<float>(window.getSize().x);
	float fHeight = static_cast<float>(window.getSize().y);

	if (m_Position.m_iScreenAnchor & 2)
	{
		sfObject->setPosition(fWidth, sfObject->getPosition().y);
	}
	else if (!(m_Position.m_iScreenAnchor & 1))
	{
		sfObject->setPosition(fWidth / 2.f, sfObject->getPosition().y);
	}
	else
	{
		sfObject->setPosition(0, sfObject->getPosition().y);
	}

	if (m_Position.m_iScreenAnchor & 8)
	{
		sfObject->setPosition(sfObject->getPosition().x, fHeight);
	}
	else if (!(m_Position.m_iScreenAnchor & 4))
	{
		sfObject->setPosition(sfObject->getPosition().x, fHeight / 2.f);
	}
	else
	{
		sfObject->setPosition(sfObject->getPosition().x, 0);
	}

	sfObject->setPosition(roundf(sfObject->getPosition().x), roundf(sfObject->getPosition().y));

	m_vScreenAnchorOGPos = sfObject->getPosition();
}

void UIObject::setOffsetPosition(sf::Transformable* sfObject, float fXOffset, float fYOffset)
{
	sfObject->setPosition(roundf(m_vScreenAnchorOGPos.x + fXOffset), roundf(sfObject->getPosition().y + fYOffset));

	m_vScreenAnchorOGPos = sfObject->getPosition();
}