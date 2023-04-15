#pragma once

#include "widget.h"
#include "menu.h"

namespace Widgets
{

class MainMenuItem : public Widget
{
public:
    MainMenuItem(const std::string& label, MenuUP menu);

    const std::string& label() const;
    void setLabel(const std::string& newLabel);

    void showMenu();
    void hideMenu();

    Menu& menu();
    Menu& menuList();

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnReposition(Utils::Position newPosition) override;

    std::string mLabel;
    MenuUP mMenu;

    bool mIsMenuShown{false};
};

}
