#include "AudioManager.h"

#include "DirectoryNavigator.h"

#include <map>
#include <assert.h>

namespace
{
	struct predicate // Not sure of a better name...
	{
		bool operator()(const std::shared_ptr<sf::Sound>& pSound) const
		{
			return pSound->getStatus() == sf::Sound::Stopped;
		}
	};
}

AudioManager::AudioManager()
{
}

AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

int AudioManager::loadSFXFromDirectory(const std::string& sFolderPath)
{
	std::vector<std::string> vFileNames = DirectoryNavigator::getFilesFromDirectory(sFolderPath);

	for (const std::string& sFileName : vFileNames)
	{
		int iDelimeterLocation = sFileName.find_first_of('.');
		std::string sPureName = sFileName.substr(0, iDelimeterLocation);
		std::string sFullName = sFolderPath + '/' + sFileName;

		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(sFullName))
		{
			// Didn't work, either not a font file type or error loading.
			continue;
		}

		m_AllSFX[sPureName] = buffer;
	}

	return m_AllSFX.size();
}

int AudioManager::loadMusicFromDirectory(const std::string& sFolderPath)
{
	std::vector<std::string> vFileNames = DirectoryNavigator::getFilesFromDirectory(sFolderPath);

	for (const std::string& sFileName : vFileNames)
	{
		int iDelimeterLocation = sFileName.find_first_of('.');
		std::string sPureName = sFileName.substr(0, iDelimeterLocation);
		std::string sFullName = sFolderPath + '/' + sFileName;

		sf::Music* music = new sf::Music();
		if (!music->openFromFile(sFullName))
		{
			continue;
		}

		m_AllMusic[sPureName].reset(music);
	}

	return m_AllMusic.size();
}

void AudioManager::playSFX(const std::string& sSFXName)
{
	assert(m_AllSFX.find(sSFXName) != m_AllSFX.end());

	std::shared_ptr<sf::Sound> pSound = std::shared_ptr<sf::Sound>(new sf::Sound(m_AllSFX.at(sSFXName)));
	pSound->play();
	m_AllSounds.push_back(pSound);
}

void AudioManager::playMusic(const std::string & sMusicName)
{
	assert(m_AllMusic.find(sMusicName) != m_AllMusic.end());

	m_AllMusic.at(sMusicName)->play();
}

void AudioManager::pauseMusic(const std::string & sMusicName, bool bRestart)
{
	assert(m_AllMusic.find(sMusicName) != m_AllMusic.end());

	if (bRestart)
	{
		m_AllMusic.at(sMusicName)->stop();
	}
	else
	{
		m_AllMusic.at(sMusicName)->pause();
	}
}

void AudioManager::toggleMusic(const std::string & sMusicName, bool bRestart)
{
	assert(m_AllMusic.find(sMusicName) != m_AllMusic.end());

	if (m_AllMusic.at(sMusicName)->getStatus() == sf::Music::Playing)
	{
		this->pauseMusic(sMusicName, bRestart);
	}
	else
	{
		this->playMusic(sMusicName);
	}
}

void AudioManager::clearStoppedSFX()
{
	// Deletion concept taken from http://stackoverflow.com/a/3938847
	std::vector<std::shared_ptr<sf::Sound>>::iterator it = std::remove_if(m_AllSounds.begin(), m_AllSounds.end(), predicate());
	m_AllSounds.erase(it, m_AllSounds.end());
}
