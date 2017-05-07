/*
Used to display still or animated images on a Screen.
Inherits from UIObject.
Other classes should inherit from UIImage if they have
a sprite that needs drawing so that they have access to
the achor setting functions.
*/

#pragma once

#include "UIObject.h"
#include "UITextureAnimator.h"
#include "UIProgrammedAnimation.h"

class UIImage : public UIObject
{
public:
	///<summary>Creates an image at a given position with a texture</summary>
	UIImage(const std::string& sTextureName, const sf::RenderWindow& window, UIPosition position);

	void setTextureAnimation(const std::string& sAnimationName);
	void setTextureAnimationSpeed(int iFrameSpeed);
	UIProgrammedAnimation& chooseProgrammedAnimation();

	void setUIPosition(const UIPosition& position, const sf::RenderWindow& window);

	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite m_Sprite;
	UITextureAnimator m_TextureAnimator;
	UIProgrammedAnimation m_ProgrammedAnimator;

private:
};