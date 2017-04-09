/*
Contains 'static' information about a spritesheet.
For example the list of animations it has, the number
of frames in each animation and their coordinates in
the texture.
*/

#pragma once

#include <map>
#include <vector>
#include "SFML\Graphics.hpp"

class UITextureAnimationInfo
{

public:
	UITextureAnimationInfo(const std::string& sTexName);

	sf::IntRect getTextureRect(const std::string& sAnimationName, int iFrameNumber);
	std::string getFirstAnimationString() const;
	int getNumOfFrames(const std::string& sAnimationName);

	int x(const std::string& sAnimationName, int iFrameNumber);
	int y(const std::string& sAnimationName, int iFrameNumber);
	int w(const std::string& sAnimationName, int iFrameNumber);
	int h(const std::string& sAnimationName, int iFrameNumber);

private:
	struct UIAnimFrameInfo
	{
		// The vector stores the order the frames should played in
		int x, y, w, h;
	};

	std::map<std::string, std::vector<UIAnimFrameInfo>> m_AllAnimations;

	void parseFile(const std::string& sTexName);
};