#pragma once

#include "widget.h"
#include "menulist.h"

namespace Widgets
{

class MainMenuItem : public Widget
{
public:
    MainMenuItem(const std::string& label, MenuList&& menuList);

    const std::string& label() const;
    void setLabel(const std::string& newLabel);

    void showMenu();
    void hideMenu();

    const MenuList& menuList() const;
    MenuList& menuList();

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnReposition(Utils::Position newPosition) override;

    std::string mLabel;
    MenuList mMenuList;

    bool mIsMenuShown{false};
};

}
