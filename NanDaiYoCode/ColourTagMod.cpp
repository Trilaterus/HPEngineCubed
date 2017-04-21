#include "ColourTagMod.h"

#include "StringHelper.h"

namespace TextTag
{
	Colour::Colour()
		:
		TextTagMod()
	{
	}

	bool Colour::validate(const std::vector<std::string>& vTagContents)
	{
		if (vTagContents.size() < 4)
		{
			return false; // Not enough colour members
		}

		for (unsigned int i = 1; i < vTagContents.size(); ++i)
		{
			if (!StringHelper::CanStringToInt(vTagContents.at(i)))
			{
				return false; // NaN
			}

			int iValue = std::stoi(vTagContents.at(i));

			if (iValue > 255 || iValue < 0)
			{
				return false; // The number is out of scope for an RGB colour value
			}
		}

		// Passed all testing, set it up!
		this->setup(vTagContents);

		return true;
	}

	void Colour::modifyText(sf::Text& sfText)
	{
		sfText.setFillColor(m_sfColour);
	}

	void Colour::setup(const std::vector<std::string>& vTagContents)
	{
		int colourValues[4] = { 0, 0, 0, 255 };

		int tagMembers = vTagContents.size() - 1;

		for (unsigned int i = 1; i < vTagContents.size(); ++i)
		{
			colourValues[i - 1] = std::stoi(vTagContents.at(i));
		}

		m_sfColour = sf::Color(colourValues[0], colourValues[1], colourValues[2], colourValues[3]);
	}
}