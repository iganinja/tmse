#include "widget.h"

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

//bool Widget::widgetOnKey(int32_t key)
//{
//    return false;
//}

//Olagarro::Tasks::TaskUP Widget::widgetTasks()
//{
//    return nullptr;
//}



}
