#pragma once

#include <vector>
#include <string>

#include "widget.h"
#include "mainmenuitem.h"

namespace Widgets
{

class MainMenu : public Widget
{
public:
    MainMenu();

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(std::size_t newWidth, std::size_t newHeight) override;

    std::vector<MainMenuItem> mItems;
};

}
