#include "widget.h"
#include "utils/terminalutils.h"

#include <utf8.h>

namespace
{

// Widget coordinate system is base 0, but cpp-terminal seems to be (1, 1) base
constexpr Utils::Position PositionOffset{1, 1};

Utils::Position mapToTerminal(const Utils::Position& p)
{
    return p + PositionOffset;
}

}

namespace Widgets
{

Widget::Widget(/*Widget* parent*/) //:
    //mParent{parent}
{
}

void Widget::draw(Term::Window& window)
{
    if(!mIsVisible)
    {
        return;
    }

    widgetDraw(window);
}

void Widget::setPosition(Utils::Position newPosition)
{
    mPosition = newPosition;
    widgetOnReposition(mPosition);
}

void Widget::setPosition(int newX, int newY)
{
    setPosition(Utils::Position{newX, newY});
}

void Widget::onResize(size_t newWidth, size_t newHeight)
{
    mSize = Utils::Size(newWidth, newHeight);
    widgetOnResize(newWidth, newHeight);
}

//bool Widget::onKey(int32_t key)
//{
//    return widgetOnKey(key);
//}

Utils::Position Widget::position() const
{
    return mPosition;
}

Utils::Size Widget::size() const
{
    return mSize;
}

bool Widget::isVisible() const
{
    return mIsVisible;
}

void Widget::setVisible(bool visible)
{
    mIsVisible = visible;
}

void Widget::show()
{
    setVisible(true);
}

void Widget::hide()
{
    setVisible(false);
}

//Widget* Widget::parent()
//{
//    return mParent;
//}

//void Widget::setParent(Widget* parent)
//{
//    mParent = parent;
//}

//std::vector<std::unique_ptr<Widget> >& Widget::children()
//{
//    return mChildren;
//}

//Widget* Widget::addChild(std::unique_ptr<Widget>&& child)
//{
//    auto widget{child.get()};

//    widget->setParent(this);
//    mChildren.emplace_back(std::move(child));

//    return widget;
//}

void Widget::widgetDraw(Term::Window& window)
{
    window.print_str(1, 1, "Not implemented");
}

void Widget::widgetOnReposition(Utils::Position newPosition)
{
}

void Widget::widgetOnResize(size_t newWidth, size_t newHeight)
{
}

void Widget::write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Window& window)
{
    const auto DummyColor{Term::Color::Name::Black};
    write(x, y, text, hAnchor, DummyColor, DummyColor, false, window);
}

void Widget::write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Color colorBG, Term::Color colorFG, Term::Window& window)
{
    write(x, y, text, hAnchor, colorBG, colorFG, true, window);
}

void Widget::write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, const ColorSetting& colors, Term::Window& window)
{
    write(x, y, text, hAnchor, colors.background, colors.foreground, true, window);
}

void Widget::drawRect(int x, int y, size_t width, size_t height, Term::Color colorBG, Term::Color colorFG, Term::Window& window)
{
    auto const terminalPosition{mapToTerminal(position() + Utils::Position{x, y})};
    Utils::fillBGFG(window, terminalPosition.x, terminalPosition.y, terminalPosition.x + width - 1, terminalPosition.y + height - 1, colorBG, colorFG);
}

void Widget::drawRect(int x, int y, size_t width, size_t height, const ColorSetting& colors, Term::Window& window)
{
    drawRect(x, y, width, height, colors.background, colors.foreground, window);
}

void Widget::drawBox(int x, int y, size_t width, size_t height, Term::Color colorBG, Term::Color colorFG, Term::Window& window)
{
    drawRect(x, y, width, height, colorBG, colorFG, window);

    auto const terminalPosition{mapToTerminal(position() + Utils::Position{x, y})};
    window.print_rect(terminalPosition.x, terminalPosition.y, terminalPosition.x + width - 1, terminalPosition.y + height - 1);
}

void Widget::drawBox(int x, int y, size_t width, size_t height, const ColorSetting& colors, Term::Window& window)
{
    drawBox(x, y, width, height, colors.background, colors.foreground, window);
}

void Widget::write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Color colorBG, Term::Color colorFG, bool useColors, Term::Window& window)
{
    auto const terminalPosition{mapToTerminal(position() + Utils::Position{x, y})};
    const auto textLength{utf8::distance(text.begin(), text.end())};
    auto textX{0};

    switch(hAnchor)
    {
    case HorizontalAnchor::Left:
        textX = terminalPosition.x;
        break;
    case HorizontalAnchor::Center:
        textX = terminalPosition.x - textLength / 2;
        break;
    case HorizontalAnchor::Right:
        textX = terminalPosition.x - textLength;
        break;
    }

    if(useColors)
    {
        Utils::fillBGFG(window, textX, terminalPosition.y, textX + textLength - 1, terminalPosition.y, colorBG, colorFG);
    }

    window.print_str(textX, terminalPosition.y, text);
}

//bool Widget::widgetOnKey(int32_t key)
//{
//    return false;
//}

//Olagarro::Tasks::TaskUP Widget::widgetTasks()
//{
//    return nullptr;
//}



}
