#include "UIPosition.h"

UIPosition::UIPosition()
	:
	m_iScreenAnchor(UIAnchor::CENTRE),
	m_iOriginAnchor(UIAnchor::CENTRE),
	m_fXOffset(0.f),
	m_fYOffset(0.f)
{
	if (!ValidateAnchor(m_iScreenAnchor))
	{
		m_iScreenAnchor = UIAnchor::CENTRE;
	}

	if (!ValidateAnchor(m_iOriginAnchor))
	{
		m_iOriginAnchor = UIAnchor::CENTRE;
	}
}

UIPosition::UIPosition(UIAnchor bothAnchors, float fXOffset, float fYOffset)
	:
	m_iScreenAnchor(bothAnchors),
	m_iOriginAnchor(bothAnchors),
	m_fXOffset(fXOffset),
	m_fYOffset(fYOffset)
{
	if (!ValidateAnchor(m_iScreenAnchor))
	{
		m_iScreenAnchor = UIAnchor::CENTRE;
	}

	if (!ValidateAnchor(m_iOriginAnchor))
	{
		m_iOriginAnchor = UIAnchor::CENTRE;
	}
}

UIPosition::UIPosition(UIAnchor screenAnchor, UIAnchor originAnchor, float fXOffset, float fYOffset)
	:
	m_iScreenAnchor(screenAnchor),
	m_iOriginAnchor(originAnchor),
	m_fXOffset(fXOffset),
	m_fYOffset(fYOffset)
{
	if (!ValidateAnchor(m_iScreenAnchor))
	{
		m_iScreenAnchor = UIAnchor::CENTRE;
	}

	if (!ValidateAnchor(m_iOriginAnchor))
	{
		m_iOriginAnchor = UIAnchor::CENTRE;
	}
}

bool UIPosition::ValidateAnchor(int iAnchors)
{
	if (iAnchors > 10 ||
		iAnchors == 3)
	{
		return false;
	}

	return true;
}