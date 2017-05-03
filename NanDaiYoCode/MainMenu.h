#pragma once

#include "Scene.h"
#include "UIButton.h"
#include "UIText.h"

namespace Screens
{
	class MainMenu : public Scene
	{
	public:
		MainMenu(const sf::RenderWindow& window);

		void handleEvents(const sf::Event& event);
		void update(float fFrameChunk);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::shared_ptr<UIButton> m_pButton;
		std::shared_ptr<UIText> m_pButtonText;

		void handleOptionsButton();
	};
}