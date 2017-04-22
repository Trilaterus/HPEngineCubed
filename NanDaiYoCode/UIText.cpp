#include "UIText.h"

#include "FontManager.h"
#include "StringHelper.h"

UIText::UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position)
	:
	UIObject(position),
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
	for (sf::Text text : m_AllTexts)
	{
		target.draw(text);
	}
}

std::vector<sf::Text> UIText::parseRawString()
{
	const std::string sRawString = m_sRawString;

	std::vector<sf::Text> AllTexts;
	std::string sCurrentString; // The currently built up string

	bool bParsingTag = false;

	float fXOffset = 0.f;
	float fYOffset = 0.f;

	char cOpenTag = '<';
	char cCloseTag = '>';
	char cDelimiter = ' ';
	char cEndTag = '/';
	std::string sBreakLineTag = "br";

	for (std::string::const_iterator cCurrentChar = sRawString.begin(); cCurrentChar != sRawString.end(); ++cCurrentChar)
	{
		if (bParsingTag)
		{
			bParsingTag = false;

			std::string::const_iterator cTagEnd = std::find(cCurrentChar, sRawString.end(), cCloseTag);

			if (cTagEnd == sRawString.end())
			{
				sCurrentString.push_back(cOpenTag);
				sCurrentString.push_back(*cCurrentChar);
				continue;
			}

			std::string sTagContents = std::string(cCurrentChar, cTagEnd);

			std::vector<std::string> vAllStrings = StringHelper::SplitString(sTagContents, cDelimiter);

			// Handling for "<>"
			if (vAllStrings.size() == 0)
			{
				sCurrentString.push_back(cOpenTag);
				sCurrentString.push_back(*cCurrentChar);
				continue;
			}

			std::shared_ptr<TextTagMod> textTag(TextTag::tagList(vAllStrings.at(0)));

			if (textTag == nullptr || !textTag->validate(vAllStrings))
			{
				sCurrentString.push_back(cOpenTag);
				sCurrentString.push_back(*cCurrentChar);
				continue;
			}

			// Check for EndTag (pop tag)
			if (vAllStrings.at(0).c_str()[0] == cEndTag)
			{
				if (m_TagStack.size() > 0)
				{
					m_TagStack.pop_back();
				}
			}
			else if (vAllStrings.at(0) == sBreakLineTag)
			{
				sf::Text sfTextModifier;
				sfTextModifier.setFont(FontManager::getInstance().getFont(m_sFontName));
				sfTextModifier.setString("|ILW"); // Use variety of letters in case character is missing/different sizes in different fonts

				fYOffset += sfTextModifier.getGlobalBounds().height;
				fXOffset = 0.f;
			}
			else // Push back tag as normal
			{
				m_TagStack.push_back(textTag);
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

			sf::Text sfTextModifier;
			sfTextModifier.setFont(FontManager::getInstance().getFont(m_sFontName));
			sfTextModifier.setString(sCurrentString);
			sfTextModifier.setPosition(fXOffset, fYOffset);

			for (std::shared_ptr<TextTagMod> pTag : m_TagStack)
			{
				pTag->modifyText(sfTextModifier);
			}

			fXOffset += sfTextModifier.getGlobalBounds().width;

			AllTexts.push_back(sfTextModifier);

			sCurrentString.clear();

			bParsingTag = true;
		}
	}

	return AllTexts;
}