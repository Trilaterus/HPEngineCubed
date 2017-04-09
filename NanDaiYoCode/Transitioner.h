/*
This Transitioner class encapsulates the info needed to transition between scenes,
including things like the sprites needed, the timings etc
*/

#pragma once

#include "Scene.h"

/* Instant */

class Instant
{
public:
	Instant();
};

/* FadeColour */

class FadeColour : public sf::Drawable
{
public:
	FadeColour();
	FadeColour(float fFullDuration, sf::Color color = sf::Color::Black); // Defaults to fade to black
	void setScenes(Scene* prevScene, Scene* nextScene);

	bool update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float m_fDuration;
	sf::Color m_Colour;
	float m_fTotalChunks;
	Scene* m_prevScene;
	Scene* m_nextScene;
	//SinMovement m_SinMovement; // Maybe add in at some point
};

/* Swipe */

class Swipe : public sf::Drawable // Do this later
{
public:
	Swipe();

	bool update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float m_fDuration;
	//enum Direction { up, down, left, right };
};

/* Transitioner */

class Transitioner : public sf::Drawable
{
public:
	Transitioner();

	void startTransition(Instant instant, Scene* prevScene, Scene* nextScene);
	void startTransition(FadeColour fadeColour, Scene* prevScene, Scene* nextScene);

	bool isTransitioning() const;

	void update(float fFrameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	bool m_isTransitioning;
	
	enum Transition
	{
		INSTANT,
		FADECOLOUR,
		SWIPE
	};

	Transition m_TransitionType;
	Instant m_InstantTransition;
	FadeColour m_FadeColourTransition;
	Swipe m_SwipeTransition;

	Scene* m_prevScene;
	Scene* m_nextScene;

	void startTransition(Scene* prevScene, Scene* nextScene);
};