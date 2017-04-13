/*
An abstract class type to classify a transition
as specifically for Screens
*/

#pragma once

#include "SceneTransition.h"

class ScreenTransition : public SceneTransition
{
public:
	ScreenTransition() {};

	virtual bool update(float fFrameChunk) = 0; // returns false when complete
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};