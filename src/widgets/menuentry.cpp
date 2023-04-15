#include "menuentry.h"
#include "utils/terminalutils.h"
#include "settings.h"

namespace Widgets
{

MenuEntry::MenuEntry(Utils::Event<void>& event) :
    mEvent{&event}
{
}

void MenuEntry::draw(int x, int y, size_t width, bool isSelected, Term::Window& window)
{
    menuEntryDraw(x, y, width, isSelected, window);
}

Utils::Event<void>& MenuEntry::event()
{
    return *mEvent;
}

size_t MenuEntry::length() const
{
    return menuEntryLength();
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

PlainMenuEntry::PlainMenuEntry(const std::string& label, Utils::Event<void>& event) :
    MenuEntry{event},
    mLabel{label}
{
}

void PlainMenuEntry::menuEntryDraw(int x, int y, size_t width, bool isSelected, Term::Window& window)
{
    if(isSelected)
    {
        Utils::fillBGFG(window,
                        x,
                        y,
                        x + width - 2 - 1,
                        y,
                        settings().menuItemCurrentItemColor);
    }
    window.print_str(x, y, mLabel);
}

size_t PlainMenuEntry::menuEntryLength() const
{
    return mLabel.length();
}

}
