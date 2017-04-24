#include "UIText.h"

#include "FontManager.h"
#include "StringHelper.h"

UIText::UIText(const std::string& sFontName, const sf::RenderTarget& target, UIPosition position, Alignment align)
	:
	UIObject(position),
	m_sFontName(sFontName),
	m_Alignment(align),
	m_sfRenderTexture(new sf::RenderTexture())
{
	m_sfRenderTexture->setSmooth(true);

	UIObject::setScreenAnchor(&m_sfTextSprite, target);
	UIObject::setOffsetPosition(&m_sfTextSprite, position.m_fXOffset, position.m_fYOffset);
}

UIText::UIText(const UIText& uiText)
	:
	UIObject(uiText.m_Position),
	m_sFontName(uiText.m_sFontName),
	m_Alignment(uiText.m_Alignment),
	m_sfRenderTexture(new sf::RenderTexture())
{
	m_sfRenderTexture->setSmooth(true);
	m_sfTextSprite = uiText.m_sfTextSprite;
	this->setText(uiText.m_sRawString);
}

void UIText::setText(const std::string& sNewText)
{
	m_sRawString = sNewText;
	m_AllTexts = parseRawString();
	this->alignTextVector();
	UIObject::setOrigin(&m_sfTextSprite, m_sfTextSprite.getGlobalBounds().width, m_sfTextSprite.getGlobalBounds().height);
}

void UIText::handleEvent()
{
}

void UIText::update(float fFrameChunk)
{
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sfTextSprite);
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
				sf::Text sfTextModifier;
				sfTextModifier.setFont(FontManager::getInstance().getFont(m_sFontName));
				sfTextModifier.setString("|ILWy_,"); // Use variety of letters in case character is missing/different sizes in different fonts (and use low letters to modifiy the height)

				fYOffset += sfTextModifier.getGlobalBounds().height;
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
			fAlignedOffset *= 1;
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

	float fTotalHeight = 0.f;

	if (m_AllTexts.size() != 0)
	{
		sf::Text text = m_AllTexts.at(0).at(0);
		text.setString("|LIWy_,");
		fTotalHeight = text.getGlobalBounds().height * m_AllTexts.size();
	}

	this->setupRenderTexture(static_cast<unsigned int>(std::ceil(fLongestLine)), static_cast<unsigned int>(std::ceil(fTotalHeight)));
}

void UIText::setupRenderTexture(unsigned int iWidth, unsigned int iHeight)
{
	m_sfRenderTexture->clear(sf::Color::Transparent);
	m_sfRenderTexture->create(iWidth, iHeight);

	for (const std::vector<sf::Text>& vectors : m_AllTexts)
	{
		for (sf::Text text : vectors)
		{
			// The combo of scaling and having BlendNone gives an OK effect to the RenderTexture (but messes up some fonts)
			text.setScale(0.999f, 0.999f);
			m_sfRenderTexture->draw(text, sf::BlendNone);
		}
	}

	m_sfRenderTexture->display();

	m_sfTextSprite.setTexture(m_sfRenderTexture->getTexture());
}
