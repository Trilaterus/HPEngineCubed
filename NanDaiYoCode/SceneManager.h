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

class SceneManager : public sf::Drawable
{
public:
	static SceneManager& getInstance();

	void pushScreen(Scene* pScene); // Performs instant transition
	void pushScreen(Scene* pScene, FadeColour fadeColour);

	void clearAndAddScreen(Scene* pScene);


	void popScreen();
	void popScreen(FadeColour fadeColour);

	//void pushOverlay(); // Try one screen first, then try 2 screens before overlay

	void handleEvents(const sf::Event& event);
	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	SceneManager();
	SceneManager(SceneManager const&);
	void operator=(SceneManager const&);

	std::vector<std::shared_ptr<Scene>> m_AllScenes;
	Transitioner m_Transitioner;

	//std::vector<Scene*> m_DrawableScenes; // May need to be a func? GetDrawableSceneList()?
};