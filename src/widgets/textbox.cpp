#include "textbox.h"
#include "settings.h"
#include "utils/stringutils.h"

#include <iostream>

namespace Widgets
{

void TextBox::setText(std::string&& text)
{
    updateText(std::move(text));
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
        drawBox(position().x, position().y, size().x, size().y, settings().menuItemColors, window);
    }
    else
    {
        drawRect(position().x, position().y, size().x, size().y, settings().menuItemColors, window);
    }

    auto p{position()};

    for(const auto& row : mWordRows)
    {
        for(auto i = 0u; i < row.size(); ++ i)
        {
            auto& word{row[i]};

            write(p.x, p.y, word, HorizontalAnchor::Left, window);
            p.x += Utils::length(word);

            if(i < row.size() - 1)
            {
                write(p.x, p.y, " ", HorizontalAnchor::Left, window);
                ++ p.x;
            }
        }
        p.x = position().x;
        ++ p.y;
    }
}

void TextBox::widgetOnResize(size_t newWidth, size_t newHeight)
{
    updateText();
}

void TextBox::updateText(std::string&& text)
{
    mWordRows.clear();
    mWordRows.push_back(Utils::split(text));
    updateText();
}

void TextBox::updateText()
{
    if(mWordRows.empty())
    {
        return;
    }

    if(mWordRows.size() > 1)
    {
        auto& allWords{mWordRows.front()};

        for(auto i = 1u; i < mWordRows.size(); ++ i)
        {
            auto& currentRowWords{mWordRows[i]};
            allWords.insert(allWords.end(), currentRowWords.begin(), currentRowWords.end());
        }

        mWordRows.resize(1u);
    }

    auto words{mWordRows.front()};
    mWordRows.clear();

    const auto rows{size().y};
    const auto maximumRowWidth{size().x};

    auto currentRow{0};
    auto currentWord{0};

    while(currentRow < rows && currentWord < words.size())
    {
        mWordRows.push_back({});

        auto currentWidth{0};

        while(currentWord < words.size() && currentWidth + Utils::length(words[currentWord]) + 1 < maximumRowWidth)
        {
            mWordRows.back().push_back(words[currentWord]);
            currentWidth += Utils::length(words[currentWord]) + 1;
            ++ currentWord;
        }

        ++ currentRow;;
    }
}

}
