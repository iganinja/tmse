#include "widget.h"

namespace Widgets
{

void Widget::draw(Term::Window& window)
{
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

void Widget::onResize(std::size_t newWidth, std::size_t newHeight)
{
    mSize = Utils::Size(newWidth, newHeight);
    widgetOnResize(newWidth, newHeight);
}

Utils::Position Widget::position() const
{
    return mPosition;
}

Utils::Size Widget::size() const
{
    return mSize;
}

void Widget::widgetDraw(Term::Window& window)
{
    window.print_str(1, 1, "Not implemented");
}

void Widget::widgetOnReposition(Utils::Position newPosition)
{
}

void Widget::widgetOnResize(std::size_t newWidth, std::size_t newHeight)
{
}



}
