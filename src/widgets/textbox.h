#pragma once

#include "widget.h"

namespace Widgets
{

class TextBox : public Widget
{
public:
    void setText(std::string&& text);

    void setDrawBorder(bool drawBorder);
    bool doesDrawBorder() const;

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(size_t newWidth, size_t newHeight) override;
    void updateText(std::string&& text);
    void updateText();

    std::vector<std::vector<std::string>> mWordRows;
    bool mDrawBorder{false};
};

}
