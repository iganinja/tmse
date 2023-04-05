#include "mainmenuitem.h"
#include "settings.h"

namespace Widgets
{

MainMenuItem::MainMenuItem(const std::string& label, MenuList&& menuList) :
    mMenuList{std::move(menuList)}
{
    setLabel(label);
}

const std::string& MainMenuItem::label() const
{
    return mLabel;
}

void MainMenuItem::setLabel(const std::string& newLabel)
{
    mLabel = " " + newLabel;
    mSize = Utils::Size{mLabel.size() + 1, 1};
}

void MainMenuItem::showMenu()
{
    mIsMenuShown = true;
}

void MainMenuItem::hideMenu()
{
    mIsMenuShown = false;
}

void MainMenuItem::widgetDraw(Term::Window& window)
{
    const auto colorBG{mIsMenuShown? settings().selectedMenuItemColor.background : settings().menuItemColor.background};
    const auto colorFG{mIsMenuShown? settings().selectedMenuItemColor.foreground : settings().menuItemColor.foreground};

    window.fill_bg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, 1, colorBG);
    window.fill_fg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, 1, colorFG);
    window.print_str(mPosition.x(), mPosition.y(), mLabel);

    if(mIsMenuShown)
    {
        mMenuList.draw(window);
    }
}

void MainMenuItem::widgetOnReposition(Utils::Position newPosition)
{
    mMenuList.setPosition(newPosition.x(), newPosition.y() + 1);
}

const MenuList& MainMenuItem::menuList() const
{
    return mMenuList;
}

MenuList& MainMenuItem::menuList()
{
    return mMenuList;
}



}
