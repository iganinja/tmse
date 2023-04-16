#include "menu.h"
#include "settings.h"
#include "utils/terminalutils.h"

namespace Widgets
{

void Menu::addEntry(MenuEntryUP&& entry)
{
    mEntries.push_back(std::move(entry));

    Utils::Size totalSize{0, 0};

    for(const auto& entry : mEntries)
    {
        totalSize.setX(std::max(totalSize.x(), entry->length() + 1));
        totalSize.setY(totalSize.y() + 1);
    }

    mSize = Utils::Size{totalSize.x() + 2, totalSize.y() + 2};
}

const std::vector<MenuEntryUP>& Menu::entries() const
{
    return mEntries;
}

void Menu::setSelectedEntry(size_t index)
{
    mSelectedEntry = index;
}

size_t Menu::selectedEntry() const
{
    return mSelectedEntry;
}

void Menu::triggerSelectedEntry()
{
    mEntries[mSelectedEntry]->event().trigger();
}

void Menu::widgetDraw(Term::Window& window)
{
    drawBox(0, 0, size().x(), size().y(), settings().selectedMenuItemColors, window);

    Utils::Position p{position().x() + 1, position().y() + 1};

    for(size_t i = 0; i < mEntries.size(); ++ i)
    {
        const auto& entry{mEntries[i]};

        entry->draw(p.x(), p.y(), size().x(), mSelectedEntry == i, window);

        p.setY(p.y() + 1);
    }
}



}
