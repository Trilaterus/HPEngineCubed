#include "EndTagMod.h"

namespace TextTag
{
	End::End()
		:
		TextTagMod()
	{
	}

	bool End::validate(const std::vector<std::string>& vTagContents)
	{
		if (vTagContents.size() != 1)
		{
			return false; // Wrong size, only needs one element
		}

		// Check for correct first char happens in TextTagList so no need here

		return true;
	}

	void End::modifyText(sf::Text& sfText)
	{
	}
}