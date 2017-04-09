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
	static AudioManager& instance();

	bool loadFromXML(const std::string& sFilePath);

	void playSound(const std::string& sName, float fPitchMod = 1);
	void playMusic(const std::string& sName);
	void stopMusic();

	///<summary>Iterate through the current sounds and all the finished sounds, unless a specific amount of sounds is passed</summary>
	///<param name = 'iNumOfSounds'>The amount of sounds to delete. If 0 then delete all the sounds</param>
	void deleteFinishedSounds(int iNumOfSounds = 0);

private:
	AudioManager();
	AudioManager(AudioManager& const);
	void operator=(AudioManager& const);

	std::unordered_map<std::string, sf::Music> m_AllMusic;
	std::unordered_map<std::string, sf::SoundBuffer> m_AllSFX;
	
	std::vector<std::unique_ptr<sf::Sound>> m_vCurrentSounds; // vector of pointers to sounds currently playing or pending deletion
};