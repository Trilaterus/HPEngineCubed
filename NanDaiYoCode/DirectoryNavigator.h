/*
A namespace of functions to find specific files and folders within
other folders. Useful to split in case the method of calling this
ever needs to be changed (support for other platforms)
*/

#pragma once

#include <vector>
#include <Windows.h>

namespace DirectoryNavigator
{
	inline std::vector<std::string> getFilesFromDirectory(const std::string& sFolderPath, const std::string& sFileExtension = "*")
	{
		// http://stackoverflow.com/a/20847429 , tl;dr windows only solution (no external libs tho)
		std::vector<std::string> vFileNames;
		std::string sSearchPath = sFolderPath + "/*." + sFileExtension;
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(sSearchPath.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					vFileNames.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));

			::FindClose(hFind);
		}

		return vFileNames;
	}

}