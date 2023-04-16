#include "mainmenuitem.h"
#include "settings.h"

namespace Widgets
{

MainMenuItem::MainMenuItem(const std::string& label, MenuUP menu) :
    mMenu{std::move(menu)}
{
    setLabel(label);
}

const std::string& MainMenuItem::label() const
{
    return mLabel;
}

void MainMenuItem::setLabel(const std::string& newLabel)
{
    mLabel = " " + newLabel + " ";
    mSize = Utils::Size{mLabel.size(), 1};
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
    const auto colorBG{mIsMenuShown? settings().selectedMenuItemColors.background : settings().menuItemColors.background};
    const auto colorFG{mIsMenuShown? settings().selectedMenuItemColors.foreground : settings().menuItemColors.foreground};

    write(0, 0, mLabel, HorizontalAnchor::Left, colorBG, colorFG, window);

    if(mIsMenuShown)
    {
        mMenu->draw(window);
    }
}

void MainMenuItem::widgetOnReposition(Utils::Position newPosition)
{
    mMenu->setPosition(newPosition.x, newPosition.y + 1);
}

Menu& MainMenuItem::menu()
{
    return *mMenu.get();
}

Menu& MainMenuItem::menuList()
{
    return *mMenu.get();
}



}
