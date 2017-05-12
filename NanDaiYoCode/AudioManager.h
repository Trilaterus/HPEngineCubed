/*
Both music and sound effects are controlled by this class.
Stores the references to the audio and also has functionality
for playing music and sfx.
*/

#pragma once

#include <SFML\Audio.hpp>
#include <unordered_map>
#include <memory>

class AudioManager
{
public:
	static AudioManager& getInstance();

	int loadSFXFromDirectory(const std::string& sFolderPath);
	int loadMusicFromDirectory(const std::string& sFolderPath);

private:
	AudioManager();
	AudioManager(AudioManager const&);
	void operator=(AudioManager const&);

	std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_AllMusic;
	std::unordered_map<std::string, sf::SoundBuffer> m_AllSFX;

};