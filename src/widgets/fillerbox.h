#pragma once

#include <cpp-terminal/color.hpp>

#include "widget.h"

namespace Widgets
{

class FillerBox : public Widget
{
public:
    FillerBox(const Term::Color& color);

private:
    void widgetDraw(Term::Window& window) override;

    Term::Color mColor;
};

}
