/*
An abstract class type to classify a transition
as specifically for Overlays
*/

#pragma once

#include "SceneTransition.h"

class OverlayTransition : public SceneTransition
{
public:
	OverlayTransition() {};

	virtual bool update(float fFrameChunk) = 0; // returns false when complete
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};