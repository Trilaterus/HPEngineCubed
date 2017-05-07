/*
The CursorManager is a singleton class that is responsible
for handling the texture and drawing of the cursor by using
UIPosition-ing
*/

#pragma once

#include "UIImage.h"
#include <memory>

class CursorManager : public sf::Drawable
{
public:
	static CursorManager& getInstance();

	void setCursorVisible(sf::RenderWindow& window, bool visible);
	void setCursor(const UIImage& image);
	UIImage& getCursorImage();

	void updateImage(float fFrameChunk);
	void updateMousePosition(const sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	CursorManager();
	CursorManager(CursorManager const&);
	void operator=(CursorManager const&);

	bool m_bSpriteVisible;
	std::unique_ptr<UIImage> m_pCursorSprite;
	float m_fXOffset;
	float m_fYOffset;
};
