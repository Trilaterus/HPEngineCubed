/*
A wrapper for sf::Texture that contains information
about whether or not the texture is an animation.
Acts as a barrier for calling 'animation' functions
as here it's checked if the animation exists.
*/

#pragma once

#include "SFML\Graphics\Texture.hpp"
#include "UITextureAnimationInfo.h"

class UITexture : public sf::Texture
{
public:
	UITexture();
	UITexture(const std::string& sFilePath);

	void addAnimation(const std::string& sFilePath);

	sf::IntRect getTextureRect(const std::string& sAnimationName, int iFrameNumber) const;
	std::string getFirstAnimationString() const;
	int getCurrentNumOfFrames(const std::string& sAnimationName) const;

private:
	UITextureAnimationInfo* m_pAnimation;
};