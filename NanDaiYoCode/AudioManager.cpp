#include "AudioManager.h"

#include "DirectoryNavigator.h"

#include <map>
#include <assert.h>

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