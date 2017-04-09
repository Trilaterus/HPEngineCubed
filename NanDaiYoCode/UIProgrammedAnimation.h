/*
A progammed animation is an animation that is better off
calculated than captured in a spritesheet. Some examples include
moving in a sine wave (similar to hovering if done on the Y axis)
or shaking to various degrees.
A programmed animation and textured animation can be applied to
the same UIImage.
*/

#pragma once

#include "SFML\System.hpp"

class SinMovement
{
public:
	SinMovement();
	SinMovement(
		float fXDistance,
		float fXSpeed,
		float fYDistance = 0.f,
		float fYSpeed = 0.f);

	sf::Vector2f update(float fFrameChunk);

private:
	float m_fXDistance;
	float m_fXSpeed;
	float m_fXTotalTime;

	float m_fYDistance;
	float m_fYSpeed;
	float m_fYTotalTime;
};

class ShakeMovement
{
public:
	ShakeMovement();
	ShakeMovement(float fRadius, float fSpeed);

	sf::Vector2f update(float fFrameChunk);

private:
	float m_fRadius;
	float m_fSpeed;
	sf::Vector2f m_vOffsets;
	float m_fTotalTime;
};

class UIProgrammedAnimation
{
public:
	UIProgrammedAnimation();

	void setSinMovement(const SinMovement& sinValues);
	void setShakeMovement(const ShakeMovement& shakeValues);

	sf::Vector2f getOffsets();

	void update(float fFrameChunk);

private:
	// Sin Movement specific stuff
	SinMovement m_SinMovement;
	ShakeMovement m_ShakeMovement;

	sf::Vector2f m_vOffsets;
};