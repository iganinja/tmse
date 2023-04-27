#include "selectionwindow.h"
#include "settings.h"

namespace Widgets
{

SelectionWindow::SelectionWindow(std::string&& title, std::string&& messageText, std::vector<std::string>&& options, size_t width, size_t messageBoxHeight, size_t listHeight) :
    mTitle{"[" + std::move(title) + "]"}
{
    onResize(width, messageBoxHeight + listHeight + 2);

    mTextBox.onResize(width - 2, messageBoxHeight);
    mTextBox.setText(std::move(messageText));

    mList.setElements(std::move(options));
    mList.onResize(width - 2, listHeight);
}

size_t SelectionWindow::selectedOption() const
{
    return mList.currentElementIndex();
}

void SelectionWindow::widgetDraw(Term::Window& window)
{
    drawBox(0, 0, size().x, size().y, settings().menuItemColors, window);
    write(2, 0, mTitle, HorizontalAnchor::Left, window);
    mTextBox.draw(window);
    mList.draw(window);
}

void SelectionWindow::widgetOnReposition(Utils::Position newPosition)
{
    mTextBox.setPosition(newPosition.x + 1, newPosition.y + 1);
    mList.setPosition(newPosition.x + 1, mTextBox.position().y + mTextBox.size().y);
}

}
