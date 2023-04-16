#include "menu.h"
#include "settings.h"

namespace Widgets
{

void Menu::addEntry(MenuEntryUP&& entry)
{
    mEntries.push_back(std::move(entry));

    Utils::Size totalSize{0, 0};

    for(const auto& entry : mEntries)
    {
        totalSize.x = std::max(totalSize.x, entry->length() + 1);
        ++ totalSize.y;
    }

    mSize = Utils::Size{totalSize.x + 2, totalSize.y + 2};
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
    drawBox(0, 0, size().x, size().y, settings().selectedMenuItemColors, window);

    Utils::Position p{position().x + 2, position().y + 2};

    for(size_t i = 0; i < mEntries.size(); ++ i)
    {
        const auto& entry{mEntries[i]};

        entry->draw(p.x, p.y, size().x, mSelectedEntry == i, window);

        ++ p.y;
    }
}



}
