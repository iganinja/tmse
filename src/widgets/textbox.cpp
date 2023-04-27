#include "textbox.h"
#include "utils/stringutils.h"

#include <utf8.h>
#include <iostream>

namespace Widgets
{

void TextBox::setText(std::string&& text)
{
    mText = std::move(text);

    updateText();
}

void TextBox::setTitle(std::string&& title)
{
    mTitle = std::move(title);

    mTitle = "[" + mTitle + "]";
    setDrawBorder(true);
}

void TextBox::setColors(const Term::Color& backgroundColor, const Term::Color& foregroundColor)
{
    mBackgroundColor = backgroundColor;
    mForegroundColor = foregroundColor;
}

void TextBox::setDrawBorder(bool drawBorder)
{
    mDrawBorder = true;
}

bool TextBox::doesDrawBorder() const
{
    return mDrawBorder;
}

void TextBox::widgetDraw(Term::Window& window)
{
    if(doesDrawBorder())
    {
        drawBox(0, 0, size().x, size().y, mBackgroundColor, mForegroundColor, window);

        if(!mTitle.empty())
        {
            write(2, 0, mTitle, HorizontalAnchor::Left, window);
        }
    }
    else
    {
        drawRect(0, 0, size().x, size().y, mBackgroundColor, mForegroundColor, window);
    }

    Utils::Position p{doesDrawBorder()? 1 : 0, doesDrawBorder()? 1 : 0};

    for(const auto& line : mLines)
    {
        write(p.x, p.y, line, HorizontalAnchor::Left, window);
        ++ p.y;
    }
}

void TextBox::widgetOnResize(size_t newWidth, size_t newHeight)
{
    updateText();
}

void TextBox::updateText(std::string&& text)
{
    mText = std::move(text);
    updateText();
}

void TextBox::updateText()
{
    if(mText.empty())
    {
        return;
    }

    const auto xOffset{doesDrawBorder()? 1 + 1 : 0};

    auto beginIt{mText.begin()};
    auto endIt{mText.begin()};
    auto lastSpaceIt{mText.begin()};

    mLines.clear();
    mLines.reserve(size().y);

    std::string line;
    line.reserve(size().x);

    Utils::replaceAll(mText, "\t", "    ");

    auto y{0};

    while(endIt != mText.end() && y < size().y)
    {
        auto currentLineLength{utf8::distance(beginIt, endIt)};

        while(currentLineLength + xOffset < size().x && endIt != mText.end())
        {
            const auto c{*endIt};

            if(c == ' ')
            {
                lastSpaceIt = endIt;
            }
            else if(c == '\n')
            {
                utf8::next(endIt, mText.end());
                break;
            }
            else if(c != '\t' && currentLineLength + xOffset == size().x - 1)
            {
                endIt = lastSpaceIt;
                break;
            }

            utf8::next(endIt, mText.end());
            currentLineLength = utf8::distance(beginIt, endIt);
        }

        if(utf8::distance(beginIt, endIt) == 0)
        {
            break;
        }

        line.insert(line.begin(), beginIt, endIt);

        Utils::trim(line, '\n');

        if(line.front() == ' ')
        {
            line.erase(0, 1);
        }

        beginIt = endIt;

        mLines.push_back(line);

        line.clear();
    }

    mLines.shrink_to_fit();
}

}
