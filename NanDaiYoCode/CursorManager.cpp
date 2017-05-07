#include "CursorManager.h"

CursorManager & CursorManager::getInstance()
{
	static CursorManager instance;
	return instance;
}

void CursorManager::setCursorVisible(sf::RenderWindow & window, bool visible)
{
	window.setMouseCursorVisible(visible);
	m_bSpriteVisible = !visible;
}

void CursorManager::setCursor(const UIImage& image)
{
	//m_pCursorSprite.reset();
	m_pCursorSprite = std::make_unique<UIImage>(image);

	m_fXOffset = m_pCursorSprite->getUIPosition().m_fXOffset;
	m_fYOffset = m_pCursorSprite->getUIPosition().m_fYOffset;
}

UIImage& CursorManager::getCursorImage()
{
	return *m_pCursorSprite;
}

void CursorManager::updateMousePosition(const sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	m_pCursorSprite->setOffsetPosition(mousePosition.x + m_fXOffset, mousePosition.y + m_fYOffset, window);
}

void CursorManager::updateImage(float fFrameChunk)
{
	m_pCursorSprite->update(fFrameChunk);
}

void CursorManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bSpriteVisible)
	{
		target.draw(*m_pCursorSprite);
	}
}

CursorManager::CursorManager()
	:
	m_bSpriteVisible(false),
	m_fXOffset(0.f),
	m_fYOffset(0.f)
{

}