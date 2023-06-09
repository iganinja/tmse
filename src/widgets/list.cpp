#include "list.h"
#include "settings.h"

#include <utf8.h>

namespace Widgets
{

void List::setElements(std::vector<std::string>&& elements)
{
    mElements = std::move(elements);
    mCurrentElementIndex = 0;
    calculateElementsLengths();
}

void List::setDrawBorder(bool drawBorder)
{
    mDrawBorder = drawBorder;
}

bool List::doesDrawBorder() const
{
    return mDrawBorder;
}

int List::currentElementIndex() const
{
    return mCurrentElementIndex;
}

void List::setCurrentElementIndex(int index)
{
    if(mElementsLengths.empty())
    {
        mCurrentElementIndex = 0;
    }

    mCurrentElementIndex = std::min(index, static_cast<int>(mElements.size() - 1));
}

void List::selectNextElement()
{
    if(mCurrentElementIndex < mElements.size() - 1)
    {
        ++ mCurrentElementIndex;
    }
}

void List::selectPreviousElement()
{
    if(mCurrentElementIndex > 0)
    {
        -- mCurrentElementIndex;
    }
}

const std::string& List::currentElement() const
{
    return mElements[mCurrentElementIndex];
}

const std::vector<std::string> List::elements() const
{
    return mElements;
}

void List::widgetDraw(Term::Window& window)
{
    if(doesDrawBorder())
    {
        drawBox(0, 0, size().x, size().y, settings().menuItemColors, window);
    }
    else
    {
        drawRect(0, 0, size().x, size().y, settings().menuItemColors, window);
    }

    const auto maximumVisibleElements{size().y - 2};
    auto elementsToPaint{static_cast<int>(mElements.size())};
    auto baseIndex{0};

    if(elementsToPaint > maximumVisibleElements)
    {
        elementsToPaint = static_cast<int>(size().y - 2);
        baseIndex = std::max(0, mCurrentElementIndex - static_cast<int>(std::floor(elementsToPaint / 2)));

        const auto offset{baseIndex + elementsToPaint - static_cast<int>(mElements.size())};

        if(offset > 0)
        {
            baseIndex -= offset;
        }
    }

    const auto x{doesDrawBorder()? 1 : 0};
    auto y{doesDrawBorder()? 1 : 0};

    const auto width{doesDrawBorder()? size().x - 2 : size().x};

    std::string boundedLineText;

    for(auto i = baseIndex; i < elementsToPaint + baseIndex; ++ i)
    {
        if(i == mCurrentElementIndex)
        {
            drawRect(x, y, width, 1, settings().selectedMenuItemColors, window);
        }

        const auto& lineText{mElements[i]};

        boundedLineText.resize(mElementsLengths[i]);
        std::copy(lineText.begin(), lineText.begin() + mElementsLengths[i], boundedLineText.begin());

        write(x + 1, y, boundedLineText, HorizontalAnchor::Left, window);

        ++ y;
    }
}

void List::widgetOnResize(size_t newWidth, size_t newHeight)
{
    calculateElementsLengths();
}

void List::calculateElementsLengths()
{
    mElementsLengths.clear();
    mElementsLengths.reserve(mElements.size());

    const auto maximumWidth{doesDrawBorder()? size().x - 2 : size().x};

    for(const auto& element : mElements)
    {
        if(element.size() < maximumWidth)
        {
            mElementsLengths.push_back(element.size());
            continue;
        }

        auto it{element.begin()};

        const auto elementLength{utf8::distance(element.begin(), element.end())};

        for(auto i = 0u; i < elementLength; ++ i)
        {
            if(utf8::distance(element.begin(), it) == maximumWidth)
            {
                mElementsLengths.push_back(std::distance(element.begin(), it));
                break;
            }

            utf8::next(it, element.end());
        }
    }
}

}
