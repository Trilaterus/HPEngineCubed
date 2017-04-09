#include "SceneManager.h"


SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::pushScreen(Scene* pScene)
{
	m_AllScenes.push_back(std::unique_ptr<Scene>(pScene));
	m_Transitioner.startTransition(Instant(), m_AllScenes.at(m_AllScenes.size() - 2).get(), m_AllScenes.back().get());
}

void SceneManager::pushScreen(Scene* pScene, FadeColour fadeColour)
{
	m_AllScenes.push_back(std::unique_ptr<Scene>(pScene));
	m_Transitioner.startTransition(fadeColour, m_AllScenes.at(m_AllScenes.size() - 2).get(), m_AllScenes.back().get());
}

void SceneManager::clearAndAddScreen(Scene* pScene)
{
	m_AllScenes.clear();
	m_AllScenes.push_back(std::unique_ptr<Scene>(pScene));
}

void SceneManager::popScreen()
{
	m_AllScenes.pop_back();
}

void SceneManager::popScreen(FadeColour fadeColour)
{
}

void SceneManager::handleEvents(const sf::Event& event)
{
	if (!m_Transitioner.isTransitioning())
	{
		// May need some null checking...
		m_AllScenes.back()->handleEvents(event);
	}
}

void SceneManager::update(float fFrameChunk)
{
	if (m_Transitioner.isTransitioning())
	{
		m_Transitioner.update(fFrameChunk);
	}
	else // Could just leave the scenes to be updating... Or handle which scene is updating witin m_Transitioner
	{
		// May need some null checking...
		m_AllScenes.back()->update(fFrameChunk);
	}
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_Transitioner.isTransitioning())
	{
		m_Transitioner.draw(target, states);
	}
	else
	{
		// May need some null checking...
		m_AllScenes.back()->draw(target, states);
	}
}

SceneManager::SceneManager()
{
	// Could do with taking in one screen at the start to reduce chance of nullpointering
}