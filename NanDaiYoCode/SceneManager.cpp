#include "SceneManager.h"

#include "TextureManager.h"

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::pushScreen(Scene* pScene)
{
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
}

void SceneManager::pushScreen(Scene* pScene, ScreenTransition* transition)
{
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
	m_Transitioner.startTransition(transition, m_AllScenes.at(m_AllScenes.size() - 2), m_AllScenes.back());
}

void SceneManager::clearAndAddScreen(Scene* pScene)
{
	m_AllScenes.clear();
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
}

void SceneManager::clearAndAddScreen(Scene* pScene, ScreenTransition* transition)
{
	std::shared_ptr<Scene> nextScene(pScene);
	m_Transitioner.startTransition(transition, m_AllScenes.back(), nextScene);
	m_AllScenes.clear();
	m_AllScenes.push_back(nextScene);
}

void SceneManager::popScene()
{
	m_AllScenes.pop_back();
}

void SceneManager::popScreen(ScreenTransition* transition)
{
	if (m_AllScenes.back()->isOverlay()) // Prevent Overlays from being popped with a transition
	{
		this->popScene();
		return;
	}

	m_Transitioner.startTransition(transition, m_AllScenes.back(), m_AllScenes.at(m_AllScenes.size() - 2));
	m_AllScenes.pop_back();
}

void SceneManager::pushOverlay(Scene* pScene)
{
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
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
	else
	{
		// May need some null checking...
		m_AllScenes.back()->update(fFrameChunk);
	}
}

void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Transitioner.isTransitioning())
	{
		target.draw(m_Transitioner);
	}
	else
	{
		// May need some null checking...
		std::vector<std::shared_ptr<Scene>> scenes = GetDrawableScenesInOrder();
		for (std::vector<std::shared_ptr<Scene>>::const_reverse_iterator it = scenes.rbegin(); it != scenes.rend(); ++it)
		{
			if ((*it)->isOverlay())
			{
				sf::Sprite sprite = sf::Sprite(TextureManager::getInstance().getTexture("pureblack"));
				sprite.setScale(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y));
				sprite.setColor(sf::Color(0, 0, 0, 125));
				target.draw(sprite);
			}

			target.draw(**it);
		}
	}
}

SceneManager::SceneManager()
{
	// Could do with taking in one screen at the start to reduce chance of nullpointering
}

std::vector<std::shared_ptr<Scene>> SceneManager::GetDrawableScenesInOrder() const
{
	std::vector<std::shared_ptr<Scene>> scenes;

	for (std::vector<std::shared_ptr<Scene>>::const_reverse_iterator it = m_AllScenes.rbegin(); it != m_AllScenes.rend(); ++it)
	{
		scenes.push_back(*it);

		if (!(*it)->isOverlay())
		{
			break;
		}
	}

	return scenes;
}
