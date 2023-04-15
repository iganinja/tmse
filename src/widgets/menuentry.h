#pragma once

#include <cpp-terminal/window.hpp>
#include <memory>

#include "utils/event.h"

namespace Widgets
{

class MenuEntry
{
public:
    MenuEntry(Utils::Event<void>& event);
    virtual ~MenuEntry() = default;
    void draw(int x, int y, size_t width, bool isSelected, Term::Window& window);

    Utils::Event<void>& event();
    size_t length() const;

protected:
    virtual void menuEntryDraw(int x, int y, size_t width, bool isSelected, Term::Window& window) = 0;
    virtual size_t menuEntryLength() const = 0;

private:
    Utils::Event<void>* mEvent;
};

using MenuEntryUP = std::unique_ptr<MenuEntry>;

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

class PlainMenuEntry : public MenuEntry
{
public:
    PlainMenuEntry(const std::string& label, Utils::Event<void>& event);

private:
    void menuEntryDraw(int x, int y, size_t width, bool isSelected, Term::Window& window) override;
    size_t menuEntryLength() const override;

    std::string mLabel;
};

}
