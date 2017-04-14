#include "Scene.h"

#include "SceneManager.h"

Scene::Scene(const sf::RenderWindow& pWindow)
	:
	m_Window(pWindow)
{

}

bool Scene::isOverlay() const
{
	return m_isOverlay;
}

void Scene::update(float fFrameChunk)
{
	for each (std::shared_ptr<UIObject> pObject in m_AllUI)
	{
		pObject->update(fFrameChunk);
	}
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (std::shared_ptr<UIObject> pObject in m_AllUI)
	{
		target.draw(*pObject);
	}
}