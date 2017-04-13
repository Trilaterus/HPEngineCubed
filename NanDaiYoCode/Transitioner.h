/*
This Transitioner class encapsulates the info needed to transition between scenes,
including things like the sprites needed, the timings etc
*/

#pragma once

#include "Scene.h"
#include "SceneTransition.h"

class Transitioner : public sf::Drawable
{
public:
	Transitioner();

	void startTransition(SceneTransition* transition, std::shared_ptr<Scene> prevScene, std::shared_ptr<Scene> nextScene);

	bool isTransitioning() const;

	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	bool m_isTransitioning;

	std::unique_ptr<SceneTransition> m_currentTransition;
};