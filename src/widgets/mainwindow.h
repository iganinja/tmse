#pragma once

#include "widget.h"
#include "fillerbox.h"
#include "mainmenu.h"

namespace Widgets
{

class MainWindow : public Widget
{
public:
    MainWindow();

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(std::size_t newWidth, std::size_t newHeight) override;

    MainMenu mMainMenu;
    FillerBox mFillerBox;
};

}