#include "UIText.h"

#include "FontManager.h"

UIText::UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position)
	:
	UIObject(position)
{
	m_Text.setFont(FontManager::getInstance().getFont(sFontName));

	UIObject::setOrigin(&m_Text, m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
	UIObject::setScreenAnchor(&m_Text, target);
	UIObject::setOffsetPosition(&m_Text, position.m_fXOffset, position.m_fYOffset);
}

void UIText::setText(const std::string& sNewText)
{
	m_Text.setString(sNewText);
	UIObject::setOrigin(&m_Text, m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
}

void UIText::handleEvent()
{
}

void UIText::update(float fFrameChunk)
{
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Text);
}