#include "UIButton.h"

UIButton::UIButton(const std::string& sTextureName, const sf::RenderTarget& target, UIPosition position)
	:
	UIImage(sTextureName, target, position)
{

}

void UIButton::handleEvent()
{
	UIImage::handleEvent();
}

void UIButton::update(float fFrameChunk)
{
	UIImage::update(fFrameChunk);
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UIImage::draw(target, states);
}