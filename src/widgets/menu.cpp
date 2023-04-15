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
    mIndex = index;
}

size_t Menu::selectedEntry() const
{
    return mIndex;
}

void Menu::widgetDraw(Term::Window& window)
{
    Utils::drawRect(window,
                    mPosition.x(),
                    mPosition.y(),
                    mPosition.x() + mSize.x() - 1,
                    mPosition.y() + mSize.y() - 1,
                    settings().selectedMenuItemColor);

    Utils::Position p{mPosition.x() + 1, mPosition.y() + 1};

    for(size_t i = 0; i < mEntries.size(); ++ i)
    {
        const auto& entry{mEntries[i]};

        entry->draw(p.x(), p.y(), mSize.x(), mIndex == i, window);

        p.setY(p.y() + 1);
    }
}



}
