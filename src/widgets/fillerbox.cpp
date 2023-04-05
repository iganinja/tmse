#include "fillerbox.h"

namespace Widgets
{

FillerBox::FillerBox(const Term::Color& color) :
    mColor{color}
{
}

void FillerBox::widgetDraw(Term::Window& window)
{
    window.fill_bg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, mColor);
    window.fill_fg(mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, mColor);
}



}
