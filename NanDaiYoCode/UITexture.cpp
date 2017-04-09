#include "UITexture.h"

UITexture::UITexture()
{
	m_pAnimation = nullptr;
	// Needed so it can be initialised in containers (without it being a pointer)
}

UITexture::UITexture(const std::string& sFilePath)
{
	m_pAnimation = nullptr;
	this->loadFromFile(sFilePath);
}

void UITexture::addAnimation(const std::string& sFilePath)
{
	m_pAnimation = new UITextureAnimationInfo(sFilePath);
}

sf::IntRect UITexture::getTextureRect(const std::string& sAnimationName, int iFrameNumber) const
{
	if (m_pAnimation == nullptr)
	{
		return sf::IntRect(0, 0, this->getSize().x, this->getSize().y);
	}

	return m_pAnimation->getTextureRect(sAnimationName, iFrameNumber);
}

std::string UITexture::getFirstAnimationString() const
{
	if (m_pAnimation == nullptr)
	{
		return std::string();
	}

	return m_pAnimation->getFirstAnimationString();
}

int UITexture::getCurrentNumOfFrames(const std::string& sAnimationName) const
{
	if (m_pAnimation == nullptr)
	{
		return 0;
	}

	return m_pAnimation->getNumOfFrames(sAnimationName);
}
