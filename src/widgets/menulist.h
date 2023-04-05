#pragma once

#include "widget.h"

namespace Widgets
{

class MenuList : public Widget
{
public:
    MenuList(std::initializer_list<std::string>&& entries);

    const std::vector<std::string>& entries() const;

    void setIndex(std::size_t index);
    std::size_t index() const;

private:
    void widgetDraw(Term::Window& window) override;

    std::vector<std::string> mEntries;

    std::size_t mIndex{0};
};

}
