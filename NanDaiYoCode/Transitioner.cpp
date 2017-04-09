#include "Transitioner.h"

Transitioner::Transitioner()
	:
	m_isTransitioning(false)
{
}

void Transitioner::startTransition(Instant instant, Scene* prevScene, Scene* nextScene)
{
	m_TransitionType = Transition::INSTANT;
	m_InstantTransition = instant;
	startTransition(prevScene, nextScene);
}

void Transitioner::startTransition(FadeColour fadeColour, Scene* prevScene, Scene* nextScene)
{
	m_TransitionType = Transition::FADECOLOUR;
	m_FadeColourTransition = fadeColour;
	m_FadeColourTransition.setScenes(prevScene, nextScene);
	startTransition(prevScene, nextScene);
}

bool Transitioner::isTransitioning() const
{
	return m_isTransitioning;
}

void Transitioner::update(float fFrameChunk)
{
	if (m_isTransitioning)
	{
		switch (m_TransitionType)
		{
		case Transition::INSTANT:
			m_isTransitioning = false; // edge case
			break;

		case Transition::FADECOLOUR:
			m_isTransitioning = m_FadeColourTransition.update(fFrameChunk);
			break;

		case Transition::SWIPE:
			break;
		}
	}
}

void Transitioner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch (m_TransitionType)
	{
	case Transition::INSTANT:
		m_nextScene->draw(target, states);
		break;

	case Transition::FADECOLOUR:
		m_FadeColourTransition.draw(target, states);
		break;

	case Transition::SWIPE:
		m_nextScene->draw(target, states); // tmp
		break;
	}
}

void Transitioner::startTransition(Scene* prevScene, Scene* nextScene)
{
	m_isTransitioning = true;
	m_prevScene = prevScene;
	m_nextScene = nextScene;
}

/* FadeColour */

FadeColour::FadeColour()
	:
	m_fDuration(0.5f),
	m_Colour(sf::Color(0, 0, 0, 0)),
	m_fTotalChunks(0.f)
{
}

FadeColour::FadeColour(float fFullDuration, sf::Color color)
	:
	m_fDuration(fFullDuration),
	m_Colour(sf::Color(color.r, color.g, color.b, 0)),
	m_fTotalChunks(0.f)
{
}

void FadeColour::setScenes(Scene * prevScene, Scene * nextScene)
{
	m_prevScene = prevScene;
	m_nextScene = nextScene;
}

bool FadeColour::update(float fFrameChunk)
{
	m_fTotalChunks += fFrameChunk;
	float fPercentDone = std::sin(m_fTotalChunks * 3.14f / m_fDuration); // range is 0 to 1

	m_Colour.a = sf::Uint8(fPercentDone * 255.f);

	if (fPercentDone < 0.025f)
	{
		m_Colour.a = 0;
		return false; // Finished transitioning
	}

	return true; // Continue transitioning
}

void FadeColour::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f((float)target.getSize().x, (float)target.getSize().y));
	shape.setFillColor(m_Colour);

	if (m_fTotalChunks < (m_fDuration / 2.f))
	{
		m_prevScene->draw(target, states);
	}
	else
	{
		m_nextScene->draw(target, states);
	}
	
	target.draw(shape);
}

/* Instant */

Instant::Instant()
{
}

/* Swipe */

Swipe::Swipe()
{
}

bool Swipe::update(float fFrameChunk)
{
	return false;
}

void Swipe::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}