#include "UIText.h"

#include "FontManager.h"
#include "StringHelper.h"

UIText::UIText(const std::string& sFontName, const sf::RenderWindow& window, UIPosition position, Alignment align)
	:
	UIObject(position),
	m_sFontName(sFontName),
	m_Alignment(align)
{
	UIObject::setScreenAnchor(&m_sfTextSprite, window);
	UIObject::setOffsetPosition(&m_sfTextSprite, position.m_fXOffset, position.m_fYOffset);
}

void UIText::setText(const std::string& sNewText)
{
	m_sRawString = sNewText;
	m_AllTexts = parseRawString();
	this->alignTextVector();
	// Set origin called in alignTextVector
}

void UIText::setUIPosition(const UIPosition & position, const sf::RenderWindow& window)
{
	UIObject::setScreenAnchor(&m_sfTextSprite, window);
	UIObject::setOffsetPosition(&m_sfTextSprite, position.m_fXOffset, position.m_fYOffset);
	this->setupOrigin();
}

void UIText::handleEvent()
{
}

void UIText::update(float fFrameChunk)
{
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::vector<sf::Text> vector : m_AllTexts)
	{
		for (const sf::Text text : vector)
		{
			target.draw(text, m_sfTextSprite.getTransform());
		}
	}
}

std::vector<std::vector<sf::Text>> UIText::parseRawString()
{
	const std::string sRawString = m_sRawString;

	std::vector<std::vector<sf::Text>> vAllLines;
	std::vector<sf::Text> vCurrentLine;
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
				fYOffset += FontManager::getInstance().getFont(m_sFontName).getLineSpacing(30); // Default value
				fXOffset = 0.f;

				vAllLines.push_back(vCurrentLine);
				vCurrentLine.clear();
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

			vCurrentLine.push_back(sfTextModifier);

			sCurrentString.clear();

			bParsingTag = true;
		}
	}

	vAllLines.push_back(vCurrentLine);

	return vAllLines;
}

void UIText::alignTextVector()
{
	float fLongestLine = 0.f;
	std::vector<float> vLineWidths;

	for (const std::vector<sf::Text>& vector : m_AllTexts)
	{
		float fLineWidth = 0.f;

		for (const sf::Text& text : vector)
		{
			fLineWidth += text.getGlobalBounds().width;
		}

		vLineWidths.push_back(fLineWidth);
		fLongestLine = std::max(fLongestLine, fLineWidth);
	}

	float fLongestLineOrigin = fLongestLine / 2.f;

	for (unsigned int i = 0; i < vLineWidths.size(); ++i)
	{
		float fLineOrigin = vLineWidths.at(i) / 2.f;
		float fOffset = fLongestLineOrigin - fLineOrigin;

		float fAlignedOffset = fOffset;

		switch (m_Alignment)
		{
		case Alignment::LEFT:
		default:
			fAlignedOffset *= 0.f;
			break;

		case Alignment::CENTRE:
			fAlignedOffset *= 1.f;
			break;

		case Alignment::RIGHT:
			fAlignedOffset *= 2.f;
			break;
		}

		for (sf::Text& text : m_AllTexts.at(i))
		{
			text.move(fAlignedOffset, 0.f);
		}
	}

	float fTotalHeight = FontManager::getInstance().getFont(m_sFontName).getLineSpacing(30) * m_AllTexts.size(); // 30 is default char size

	UIObject::setOrigin(&m_sfTextSprite, fLongestLine, fTotalHeight);
}

void UIText::setupOrigin()
{
	float fLongestLine = 0.f;

	for (const std::vector<sf::Text>& vector : m_AllTexts)
	{
		float fLineWidth = 0.f;

		for (const sf::Text& text : vector)
		{
			fLineWidth += text.getGlobalBounds().width;
		}

		fLongestLine = std::max(fLongestLine, fLineWidth);
	}

	float fTotalHeight = FontManager::getInstance().getFont(m_sFontName).getLineSpacing(30) * m_AllTexts.size(); // 30 is default char size

	UIObject::setOrigin(&m_sfTextSprite, fLongestLine, fTotalHeight);
}
