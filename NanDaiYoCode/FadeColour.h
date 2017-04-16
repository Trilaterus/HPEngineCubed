/*
A class for defining a Screen transition that
fades the screen fully to a defined colour over
a define period of time (using sin so it's super
smooth looking!)
*/

#pragma once

#include "SceneTransition.h"

namespace Transition
{
	class FadeColour : public SceneTransition
	{
	public:
		FadeColour();
		FadeColour(float fFullDuration, sf::Color color = sf::Color::Black); // Defaults to fade to black

		bool update(float fFrameChunk);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		float m_fDuration;
		sf::Color m_Colour;
		float m_fTotalChunks;
	};
}