#include "Transitioner.h"

Transitioner::Transitioner()
	:
	m_isTransitioning(false),
	m_currentTransition(nullptr)
{
}

void Transitioner::startTransition(SceneTransition* transition, std::shared_ptr<Scene> prevScene, std::shared_ptr<Scene> nextScene)
{
	m_currentTransition.reset(transition);
	
	m_currentTransition->setScenes(prevScene, nextScene);
	m_isTransitioning = true;
}

bool Transitioner::isTransitioning() const
{
	return m_isTransitioning;
}

void Transitioner::update(float fFrameChunk)
{
	if (m_isTransitioning)
	{
		m_isTransitioning = m_currentTransition->update(fFrameChunk);
		m_currentTransition.release(); // delete transition once it's done (unneeded?)
	}
}

void Transitioner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_currentTransition->draw(target, states);
}