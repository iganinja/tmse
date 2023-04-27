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
        drawBox(0, 0, size().x, size().y, settings().menuItemColors, window);
    }
    else
    {
        drawRect(0, 0, size().x, size().y, settings().menuItemColors, window);
    }

    Utils::Position p{0, 0};

    for(const auto& row : mWordRows)
    {
        for(auto i = 0u; i < row.size(); ++ i)
        {
            auto& word{row[i]};

            if(word == "\n")
            {
                break;
            }

            write(p.x, p.y, word, HorizontalAnchor::Left, window);
            p.x += Utils::length(word);

            if(i < row.size() - 1)
            {
                write(p.x, p.y, " ", HorizontalAnchor::Left, window);
                ++ p.x;
            }
        }
        p.x = 0;
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

void mergeAllWordsInOneVector(std::vector<std::vector<std::string>>& wordRows)
{
    if(wordRows.size() > 1)
    {
        auto& allWords{wordRows.front()};

        for(auto i = 1u; i < wordRows.size(); ++ i)
        {
            auto& currentRowWords{wordRows[i]};
            allWords.insert(allWords.end(), currentRowWords.begin(), currentRowWords.end());
        }

        wordRows.resize(1u);
    }
}

void processWords(std::vector<std::string>& words)
{
    auto it{words.begin()};

    constexpr char SpecialCharacters[]{'\n', '\t'};

    std::string word;

    while(it != words.end())
    {
        word = *it;

        for(auto specialCharacter : SpecialCharacters)
        {
            if(word.find(specialCharacter) != std::string::npos)
            {
                const auto subWords{Utils::split(word, specialCharacter)};

                for(const auto& subWord : subWords)
                {
                    it = words.insert(it, subWord);
                }
            }
        }

        ++ it;
    }
}

void TextBox::updateText()
{
    if(mWordRows.empty())
    {
        return;
    }

    mergeAllWordsInOneVector(mWordRows);

    auto words{mWordRows.front()};

    processWords(words);

    mWordRows.clear();

    const auto rows{size().y};
    const auto maximumRowWidth{size().x};

    auto currentRow{0};
    auto currentWord{0};

    while(currentRow <= rows && currentWord < words.size())
    {
        mWordRows.push_back({});

        auto currentWidth{0};

        while(currentWord < words.size() && words[currentWord] != "\n" && currentWidth + Utils::length(words[currentWord]) + 1 < maximumRowWidth)
        {
            mWordRows.back().push_back(words[currentWord]);
            currentWidth += Utils::length(words[currentWord]) + 1;
            ++ currentWord;
        }

        // Perhaps one more word fits without the space character
        if(currentWord < words.size())
        {
            if(words[currentWord] == "\n")
            {
                mWordRows.back().push_back(words[currentWord]);
            }
            else if(currentWidth + Utils::length(words[currentWord]) <= maximumRowWidth)
            {
                mWordRows.back().push_back(words[currentWord]);
                ++ currentWord;
            }
        }

        ++ currentRow;;
    }
}

}
