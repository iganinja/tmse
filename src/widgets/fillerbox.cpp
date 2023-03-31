#include "fillerbox.h"

namespace Widgets
{

FillerBox::FillerBox(const Term::Color& color) :
    mColor{color}
{
}

void FillerBox::widgetDraw(Term::Window& window)
{
    window.fill_bg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, Term::Color::Name::Red);
    window.fill_fg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, Term::Color::Name::Blue);
    window.print_rect(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1);
    window.print_str(3, 2, "size: (" + std::to_string(mSize.x()) + ", " + std::to_string(mSize.y()) + ")");
}



}
