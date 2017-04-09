#include "TextureManager.h"

#include "DirectoryNavigator.h"

#include <map>
#include <assert.h>

TextureManager::TextureManager()
{

}

TextureManager& TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}



int TextureManager::loadFromDirectory(const std::string& sFolderPath)
{
	std::vector<std::string> vFileNames = DirectoryNavigator::getFilesFromDirectory(sFolderPath);

	std::map<std::string, std::string> vSheetNames;
	for each (std::string sFileName in vFileNames)
	{
		int iDelimiterLocation = sFileName.find_first_of('.');
		std::string sExtension = sFileName.substr(iDelimiterLocation);
		std::string sPureName = sFileName.substr(0, iDelimiterLocation);
		std::string sFullPath = sFolderPath + "/" + sFileName;

		if (sExtension == ".png")
		{
			m_AllTextures[sPureName] = UITexture(sFullPath);
			if (vSheetNames.find(sPureName) != vSheetNames.end())
			{
				m_AllTextures.at(sPureName).addAnimation(vSheetNames.at(sPureName));
			}
		}
		else if (sExtension == ".sprites")
		{
			vSheetNames[sPureName] = sFullPath;
			if (m_AllTextures.find(sPureName) != m_AllTextures.end())
			{
				m_AllTextures.at(sPureName).addAnimation(vSheetNames.at(sPureName));
			}
		}
	}

	return m_AllTextures.size();
}

const UITexture& TextureManager::getTexture(const std::string& sName) const
{
	assert(m_AllTextures.find(sName) != m_AllTextures.end());

	return m_AllTextures.at(sName);
}