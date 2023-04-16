#include "mainmenu.h"
#include "menu.h"
#include "settings.h"
#include "localization.h"
#include "utils/terminalutils.h"

#include <vector>
#include <tuple>
#include <cassert>

namespace Widgets
{

using namespace std::string_literals;

MainMenu::MainMenu()
{
    auto makeEntry = [](std::string&& label, Utils::Event<void>& event)
    {
        return std::unique_ptr<MenuEntry>{new PlainMenuEntry{label, event}};
    };

    auto fileMenu{std::make_unique<Menu>()};
    fileMenu->addEntry(makeEntry(tr("New"), newFile));
    fileMenu->addEntry(makeEntry(tr("Open..."), openFile));
    fileMenu->addEntry(makeEntry(tr("Save"), saveFile));
    fileMenu->addEntry(makeEntry(tr("Save as..."), saveFileAs));
    fileMenu->addEntry(makeEntry(tr("Close"), closeFile));
    fileMenu->addEntry(makeEntry(tr("Exit"), exitApp));

    auto editMenu{std::make_unique<Menu>()};
    editMenu->addEntry(makeEntry(tr("Undo"), undo));
    editMenu->addEntry(makeEntry(tr("Redo"), redo));

    auto helpMenu{std::make_unique<Menu>()};
    helpMenu->addEntry(makeEntry(tr("About..."), aboutApp));

    std::vector<std::tuple<std::string, MenuUP>> menuEntries;
    menuEntries.emplace_back(std::make_tuple(tr("File"), std::move(fileMenu)));
    menuEntries.emplace_back(std::make_tuple(tr("Edit"), std::move(editMenu)));
    menuEntries.emplace_back(std::make_tuple(tr("Help"), std::move(helpMenu)));

    for(auto& entry : menuEntries)
    {
        mItems.emplace_back(MainMenuItem{std::get<0>(entry), std::move(std::get<1>(entry))});
    }
}

void MainMenu::showMenu(size_t index)
{
    assert(index < menuNumber() && "Provided index is out of bounds");

    mCurrentMenuIndex = index;

    for(size_t i = 0; i < menuNumber(); ++ i)
    {
        if(i == mCurrentMenuIndex)
        {
            mItems[i].showMenu();
            mItems[i].menu().setSelectedEntry(0);
        }
        else
        {
            mItems[i].hideMenu();
        }
    }
}

size_t MainMenu::menuNumber() const
{
    return mItems.size();
}

Menu& MainMenu::currentMenu()
{
    return mItems[mCurrentMenuIndex].menu();
}

size_t MainMenu::currentMenuIndex() const
{
    return mCurrentMenuIndex;
}

void MainMenu::widgetDraw(Term::Window& window)
{
    drawRect(0, 0, size().x, size().y, settings().mainMenuColors, window);

    for(auto& item : mItems)
    {
        item.draw(window);
    }
}

void MainMenu::widgetOnResize(size_t newWidth, size_t newHeight)
{
    int currentX = 0;

    for(auto& item : mItems)
    {
        item.setPosition(currentX, position().y);
        currentX += item.size().x;
    }
}



}
