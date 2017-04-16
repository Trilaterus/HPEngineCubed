/*
Stores single copies of fonts so that if multiple objects
need that font it doesn't copy the same font in memory.
Not sure if fonts are huge files but still nice to have
all fonts in one place.
*/

#pragma once

#include <unordered_map>
#include <SFML\Graphics\Font.hpp>

class FontManager
{
public:
	static FontManager& getInstance();

	int loadFromDirectory(const std::string& sFolderPath);
	const sf::Font& getFont(const std::string& sName) const;

private:
	FontManager();
	FontManager(FontManager const&);
	void operator=(FontManager const&);

	std::unordered_map<std::string, sf::Font> m_AllFonts;
};