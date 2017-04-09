/*
Scene is an abstract class to allow Screens and Overlays to
be stored in the same container. A scene is essentially a small
rectangle in which UI elements can be drawn and handled within.

Cuz of circular dependencies may need some middleman class,
something like a transitionsmanager? That only handles switching
between scenes? By grabbing the current scene and a scene from
scene manager? Who knows...
*/

#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "UIObject.h"
#include <memory>

class Scene : public sf::Drawable
{
public:
	Scene(const sf::RenderWindow& window);

	/*
		Maybe copy the core SceneManager funcs here to don't need to #include
		in every other Scene class... Either that or could try to store a 
		reference to the static obj here so that can just access it?
	*/

	virtual void handleEvents(const sf::Event& event) = 0;
	virtual void update(float fFrameChunk);	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::vector<std::shared_ptr<UIObject>> m_AllUI;
	bool m_isOverlay;
	const sf::RenderWindow& m_Window;

private:

};