/*
Stores single copies of textures so that if multiple objects
need that texture it doesn't copy the same texture in memory.
This singleton will also store spritesheets and backgrounds
but has no knowledge of what they are. Everythings just a texture.
*/

#pragma once

#include <unordered_map>
#include "UITexture.h"

class TextureManager
{
public:
	static TextureManager& getInstance();

	int loadFromDirectory(const std::string& sFolderPath);
	const UITexture& getTexture(const std::string& sName) const;

private:
	TextureManager();
	TextureManager(TextureManager const&);
	void operator=(TextureManager const&);

	std::unordered_map<std::string, UITexture> m_AllTextures;
};