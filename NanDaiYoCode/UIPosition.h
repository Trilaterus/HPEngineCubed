/*
A encapsulated class containing the bare minimum information
needed to position a UI object on the screen
*/

#pragma once

#include "UIAnchorEnum.h"

class UIPosition
{
public:
	UIPosition();

	///<summary>Sets both anchors</summary>
	UIPosition(
		UIAnchor bothAnchors,
		float fXOffset = 0.f,
		float fYOffset = 0.f);

	UIPosition(
		UIAnchor screenAnchor,
		UIAnchor originAnchor,
		float fXOffset = 0.f,
		float fYOffset = 0.f);

	int m_iScreenAnchor; // Start position on screen (as a collection of flags)
	int m_iOriginAnchor; // Point of UI that is considered the centre (as a collection of flags)
	float m_fXOffset; // Offset from screen anchor + center anchor
	float m_fYOffset;

private:
	bool ValidateAnchor(int iAnchors);
};