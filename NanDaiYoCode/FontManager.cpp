#include "FontManager.h"

#include "DirectoryNavigator.h"

FontManager::FontManager()
{

}

FontManager& FontManager::getInstance()
{
	static FontManager instance;
	return instance;
}

int FontManager::loadFromDirectory(const std::string& sFolderPath)
{
	std::vector<std::string> vFileNames = DirectoryNavigator::getFilesFromDirectory(sFolderPath);
	
	for (std::string sFileName : vFileNames)
	{
		int iDelimeterLocation = sFileName.find_first_of('.');
		std::string sPureName = sFileName.substr(0, iDelimeterLocation);
		std::string sFullName = sFolderPath + '/' + sFileName;
	
		sf::Font font;
		if (!font.loadFromFile(sFullName))
		{
			// Didn't work, either not a font file type or error loading.
			continue;
		}
	
		m_AllFonts[sPureName] = font;
	}
	
	return m_AllFonts.size();
}

const sf::Font& FontManager::getFont(const std::string& sName) const
{
	return m_AllFonts.at(sName);
}
