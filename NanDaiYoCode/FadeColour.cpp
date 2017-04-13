#include "FadeColour.h"

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

bool FadeColour::update(float fFrameChunk)
{
	m_fTotalChunks += fFrameChunk;
	float fPercentDone = std::sin(m_fTotalChunks * 3.14f / m_fDuration); // range is 0 to 1

	m_Colour.a = sf::Uint8(fPercentDone * 255.f);

	if (fPercentDone < 0.025f)
	{
		m_Colour.a = 0;
		m_prevScene.reset();
		m_nextScene.reset();
		return false; // Finished transitioning
	}

	return true; // Continue transitioning
}

void FadeColour::draw(sf::RenderTarget& target, sf::RenderStates states) const
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