#pragma once

#include "widget.h"
#include "menuentry.h"

namespace Widgets
{

class Menu : public Widget
{
public:
    void addEntry(MenuEntryUP&& entry);
    const std::vector<MenuEntryUP>& entries() const;

    void setSelectedEntry(size_t index);
    size_t selectedEntry() const;

    void triggerSelectedEntry();

private:
    void widgetDraw(Term::Window& window) override;

    std::vector<MenuEntryUP> mEntries;

    size_t mSelectedEntry{0};
};

using MenuUP = std::unique_ptr<Menu>;

}
