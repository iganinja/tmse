#pragma once

#include "widget.h"

namespace Widgets
{

class TextBox : public Widget
{
public:
    void setText(std::string&& text);

    // Setting a title enables border
    void setTitle(std::string&& title);

    void setColors(const Term::Color& backgroundColor, const Term::Color& foreground);

    void setDrawBorder(bool drawBorder);
    bool doesDrawBorder() const;

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(size_t newWidth, size_t newHeight) override;
    void updateText(std::string&& text);
    void updateText();

    std::string mText;
    std::string mTitle;
    std::vector<std::string> mLines;
    bool mDrawBorder{false};
    Term::Color mBackgroundColor{Term::Color::Name::Red};
    Term::Color mForegroundColor{Term::Color::Name::BrightWhite};
};

}
