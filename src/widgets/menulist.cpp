#include "menulist.h"
#include "settings.h"
#include "utils/terminalutils.h"

namespace Widgets
{

MenuList::MenuList(std::initializer_list<std::string>&& entries) :
    mEntries{std::move(entries)}
{
    Utils::Size totalSize{0, 0};

    for(const auto& entry : mEntries)
    {
        totalSize.setX(std::max(totalSize.x(), entry.length() + 1));
        totalSize.setY(totalSize.y() + 1);
    }

    mSize = Utils::Size{totalSize.x() + 2, totalSize.y() + 2};
}

const std::vector<std::string>& MenuList::entries() const
{
    return mEntries;
}

void MenuList::setIndex(std::size_t index)
{
    mIndex = index;
}

std::size_t MenuList::index() const
{
    return mIndex;
}

void MenuList::widgetDraw(Term::Window& window)
{
    Utils::drawRect(window,
                    mPosition.x(),
                    mPosition.y(),
                    mPosition.x() + mSize.x() - 1,
                    mPosition.y() + mSize.y() - 1,
                    settings().selectedMenuItemColor);

    Utils::Position p{mPosition.x() + 1, mPosition.y() + 1};

    for(std::size_t i = 0; i < mEntries.size(); ++ i)
    {
        const auto& entry{mEntries[i]};

        if(mIndex == i)
        {
            Utils::fillBGFG(window,
                            p.x(),
                            p.y(),
                            p.x() + mSize.x() - 2 - 1,
                            p.y(),
                            settings().menuItemCurrentItemColor);
        }

        window.print_str(p.x(), p.y(), entry);
        p.setY(p.y() + 1);
    }
}



}
