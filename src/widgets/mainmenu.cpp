#include "mainmenu.h"
#include "menulist.h"
#include "settings.h"
#include "localization.h"

#include <vector>
#include <tuple>

namespace Widgets
{

using namespace std::string_literals;

MainMenu::MainMenu()
{
    std::vector<std::tuple<std::string, MenuList>> menuEntries
    {
        std::make_tuple(tr("File"), MenuList{tr("Open..."), tr("Save"), tr("Save as..."), tr("Close"), tr("Exit")}),
        std::make_tuple(tr("Edit"), MenuList{tr("Undo"), tr("Redo")}),
        std::make_tuple(tr("Help"), MenuList{tr("About")})
    };

    for(auto& entry : menuEntries)
    {
        mItems.emplace_back(MainMenuItem{std::get<0>(entry), std::move(std::get<1>(entry))});
    }

    mItems[0].showMenu();
}

void MainMenu::widgetDraw(Term::Window& window)
{
    window.fill_bg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, settings().mainMenuColor.background);
    window.fill_fg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, settings().mainMenuColor.background);

    for(auto& item : mItems)
    {
        item.draw(window);
    }
}

void MainMenu::widgetOnResize(std::size_t newWidth, std::size_t newHeight)
{
    int currentX = 1;

    for(auto& item : mItems)
    {
        item.setPosition(currentX, mPosition.y());
        currentX += item.size().x();
    }
}



}
