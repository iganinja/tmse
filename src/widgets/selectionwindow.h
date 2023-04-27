#pragma once

#include "widget.h"
#include "textbox.h"
#include "list.h"

namespace Widgets
{

class SelectionWindow : public Widget
{
public:
    SelectionWindow(std::string&& title, std::string&& messageText, std::vector<std::string>&& options, size_t width, size_t messageBoxHeight, size_t listHeight);
    size_t selectedOption() const;

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnReposition(Utils::Position newPosition) override;

    std::string mTitle;
    TextBox mTextBox;
    List mList;
};

}
