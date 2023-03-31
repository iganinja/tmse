#pragma once

#include <cpp-terminal/window.hpp>
#include <memory>

#include "utils/size.h"

namespace Widgets
{

class Widget
{
public:
    virtual ~Widget() = default;

    void draw(Term::Window& window);
    void setPosition(Utils::Position newPosition);
    void onResize(std::size_t newWidth, std::size_t newHeight);

    Utils::Position position() const;
    Utils::Size size() const;

    enum class SizeFlags
    {
        Fixed,
        Expanding
    };

    using SizeBehavior = Utils::Vector2D<SizeFlags>;

    SizeBehavior sizeBehavior() const;

protected:
    virtual void widgetDraw(Term::Window& window);
    virtual void widgetOnResize(std::size_t newWidth, std::size_t newHeight);

    Utils::Position mPosition{1, 1};
    Utils::Size mSize;
    SizeBehavior mSizeBehavior{SizeFlags::Expanding, SizeFlags::Expanding};
};

using WidgetUP = std::unique_ptr<Widget>;

}
