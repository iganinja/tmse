#pragma once

#include "widget.h"

namespace Widgets
{

class List : public Widget
{
public:
    void setElements(std::vector<std::string>&& elements);

    void setDrawBorder(bool drawBorder);
    bool doesDrawBorder() const;

    int currentElementIndex() const;
    void setCurrentElementIndex(int index);
    void selectNextElement();
    void selectPreviousElement();
    const std::string& currentElement() const;
    const std::vector<std::string> elements() const;

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(size_t newWidth, size_t newHeight) override;
    void calculateElementsLengths();


    std::vector<std::string> mElements;
    int mCurrentElementIndex{0};
    std::vector<size_t> mElementsLengths;
    bool mDrawBorder{false};
};

}
