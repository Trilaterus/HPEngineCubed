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

UIImage& CursorManager::setCursor(const UIImage& image)
{
	//m_pCursorSprite.reset();
	m_pCursorSprite = std::make_unique<UIImage>(image);
	
	return *m_pCursorSprite;
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
	m_bSpriteVisible(false)
{

}