#include "UIText.h"

#include "FontManager.h"
#include "StringHelper.h"

UIText::UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position)
	:
	UIObject(position),
	m_sColourTag("c"),
	m_sFontName(sFontName)
{
	//UIObject::setOrigin(&m_Text, m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
	//UIObject::setScreenAnchor(&m_Text, target);
	//UIObject::setOffsetPosition(&m_Text, position.m_fXOffset, position.m_fYOffset);
}

void UIText::setText(const std::string& sNewText)
{
	m_sRawString = sNewText;
	//UIObject::setOrigin(&m_Text, m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
	m_AllTexts = parseRawString();
}

void UIText::handleEvent()
{
}

void UIText::update(float fFrameChunk)
{
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	float fXOffset = 0.f;

	for (sf::Text text : m_AllTexts)
	{
		text.move(fXOffset, 0.f);

		target.draw(text);

		fXOffset += text.getGlobalBounds().width;
	}
}

std::vector<sf::Text> UIText::parseRawString()
{
	const std::string sRawString = m_sRawString;

	std::vector<sf::Text> AllTexts;
	std::string sCurrentString; // The currently built up string
	sf::Text sfTextModifier; // The current modifiers to the text
	sfTextModifier.setFont(FontManager::getInstance().getFont(m_sFontName));

	bool bParsingTag = false;

	char cOpenTag = '<';
	char cCloseTag = '>';
	char cDelimiter = ' ';

	for (std::string::const_iterator cCurrentChar = sRawString.begin(); cCurrentChar != sRawString.end(); ++cCurrentChar)
	{
		if (bParsingTag)
		{
			bParsingTag = false;

			// Validate rest of tag
			std::string::const_iterator cTagEnd = std::find(cCurrentChar, sRawString.end(), cCloseTag);

			if (cTagEnd == sRawString.end())
			{
				sCurrentString.push_back(cOpenTag);
				sCurrentString.push_back(*cCurrentChar);
				continue;
			}

			std::string sTagContents = std::string(cCurrentChar, cTagEnd);

			std::vector<std::string> vAllStrings = StringHelper::SplitString(sTagContents, cDelimiter);

			if (validateTagContents(vAllStrings))
			{
				updateTextModifier(sfTextModifier, vAllStrings);
			}
			else
			{
				sCurrentString.push_back(cOpenTag);
				sCurrentString.push_back(*cCurrentChar);
				continue;
			}

			std::advance(cCurrentChar, cTagEnd - cCurrentChar);
		}
		else
		{
			if (*cCurrentChar != cOpenTag)
			{
				sCurrentString.push_back(*cCurrentChar);

				if (cCurrentChar + 1 != sRawString.end())
				{
					continue;
				}
			}

			// End building current string
			sfTextModifier.setString(sCurrentString);
			AllTexts.push_back(sfTextModifier);

			sCurrentString.clear();

			bParsingTag = true;
		}
	}
	// End of input string

	return AllTexts;
}

bool UIText::validateTagContents(const std::vector<std::string>& vTagContents)
{
	if (vTagContents.empty())
	{
		return false;
	}

	if (vTagContents.at(0) == m_sColourTag)
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

		return true;
	}

	return false; // Unrecognised first tag
}

void UIText::updateTextModifier(sf::Text& modifier, const std::vector<std::string>& vTagContents)
{
	// TagContents has been validated so assume it's safe
	if (vTagContents.at(0) == m_sColourTag)
	{
		int colourValues[4] = { 0, 0, 0, 255 };

		int tagMembers = vTagContents.size() - 1;

		for (unsigned int i = 1; i < vTagContents.size(); ++i)
		{
			colourValues[i - 1] = std::stoi(vTagContents.at(i));
		}

		modifier.setFillColor(sf::Color(colourValues[0], colourValues[1], colourValues[2], colourValues[4]));

		return;
	}
}
