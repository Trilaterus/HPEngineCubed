#include "UIProgrammedAnimation.h"

#include "RandomResource.h"
#include <cmath>

/* UIProgrammedAnimation */

UIProgrammedAnimation::UIProgrammedAnimation()
	:
	m_vOffsets(0.f, 0.f)
{

}

void UIProgrammedAnimation::setSinMovement(const SinMovement& sinValues)
{
	m_SinMovement = sinValues;
}

void UIProgrammedAnimation::setShakeMovement(const ShakeMovement & shakeValues)
{
	m_ShakeMovement = shakeValues;
}

sf::Vector2f UIProgrammedAnimation::getOffsets()
{
	return m_vOffsets;
}

void UIProgrammedAnimation::update(float fFrameChunk)
{
	m_vOffsets = m_SinMovement.update(fFrameChunk);
	
	m_vOffsets += m_ShakeMovement.update(fFrameChunk);
}

/* SinMovement */

SinMovement::SinMovement()
	:
	m_fXDistance(0.f),
	m_fXSpeed(0.f),
	m_fYDistance(0.f),
	m_fYSpeed(0.f),
	m_fXTotalTime(0.f),
	m_fYTotalTime(0.f)
{

}

SinMovement::SinMovement(float fXDistance, float fXSpeed, float fYDistance, float fYSpeed)
	:
	m_fXDistance(fXDistance),
	m_fXSpeed(fXSpeed),
	m_fYDistance(fYDistance),
	m_fYSpeed(fYSpeed),
	m_fXTotalTime(0.f),
	m_fYTotalTime(0.f)
{

}

sf::Vector2f SinMovement::update(float fFrameChunk)
{
	m_fXTotalTime += fFrameChunk * m_fXSpeed;
	m_fYTotalTime += fFrameChunk * m_fYSpeed;

	return sf::Vector2f(
		std::sin(m_fXTotalTime) * m_fXDistance,
		std::sin(m_fYTotalTime) * m_fYDistance);
}

/* Shake Movement */

ShakeMovement::ShakeMovement()
	:
	m_fRadius(0.f),
	m_fSpeed(0.f),
	m_vOffsets(0.f, 0.f),
	m_fTotalTime(0.f)
{
}

ShakeMovement::ShakeMovement(float fRadius, float fSpeed)
	:
	m_fRadius(fRadius),
	m_fSpeed(fSpeed),
	m_vOffsets(0.f, 0.f),
	m_fTotalTime(0.f)
{
}

sf::Vector2f ShakeMovement::update(float fFrameChunk)
{
	m_fTotalTime += fFrameChunk;

	if (m_fTotalTime < 1.f / m_fSpeed)
	{
		return m_vOffsets;
	}

	m_fTotalTime -= 1.f / m_fSpeed;

	float fRandAngle = RandomResource::generateFloat(0.f, 360.f);

	m_vOffsets = sf::Vector2f(
		m_fRadius * std::sin(fRandAngle),
		m_fRadius * std::cos(fRandAngle));

	return m_vOffsets;
}
