/*
The SceneManager is a singleton / static class. It contains
a stack of the current Screens and Overlays open. The topmost
Screen and Overlays above it are drawn, with the utmost top screen/overlay
being updated and event handled.
*/

#pragma once

#include <vector>
#include "Scene.h"
#include <memory>
#include "Transitioner.h"
#include "SceneTransition.h"

class SceneManager : public sf::Drawable
{
public:
	static SceneManager& getInstance();

	void pushScreen(Scene* pScene); // Performs instant transition
	void pushScreen(Scene* pScene, SceneTransition* transition);

	void clearAndAddScreen(Scene* pScene);
	void clearAndAddScreen(Scene* pScene, SceneTransition* transition);

	void popScene(); // Use this for all Overalys and Instant Screen
	void popScreen(SceneTransition* transition);

	void pushOverlay(Scene* pScene);

	void handleEvents(const sf::Event& event);
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	SceneManager();
	SceneManager(SceneManager const&);
	void operator=(SceneManager const&);

	std::vector<std::shared_ptr<Scene>> m_AllScenes;
	Transitioner m_Transitioner;

	std::vector<std::shared_ptr<Scene>> GetDrawableScenesInOrder() const;
};