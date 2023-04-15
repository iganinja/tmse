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

    void showMenu(size_t index);
    size_t menuNumber() const;

    Menu& currentMenu();
    size_t currentMenuIndex() const;

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
    size_t mCurrentMenuIndex{0};
};

}
