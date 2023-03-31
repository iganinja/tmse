#pragma once

#include "widget.h"

namespace Widgets
{

class MainMenu : public Widget
{
public:
    MainMenu();

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(std::size_t newWidth, std::size_t newHeight) override;
};

}
