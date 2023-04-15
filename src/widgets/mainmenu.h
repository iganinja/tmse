#pragma once

#include <vector>
#include <string>

#include "widget.h"
#include "mainmenuitem.h"
#include "utils/event.h"

namespace Widgets
{

class MainMenu : public Widget
{
public:
    MainMenu();

    Utils::Event<void> newFile;
    Utils::Event<void> openFile;
    Utils::Event<void> saveFile;
    Utils::Event<void> saveFileAs;
    Utils::Event<void> closeFile;
    Utils::Event<void> exitApp;

    Utils::Event<void> undo;
    Utils::Event<void> redo;

    Utils::Event<void> aboutApp;

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(size_t newWidth, size_t newHeight) override;

    std::vector<MainMenuItem> mItems;
};

}
