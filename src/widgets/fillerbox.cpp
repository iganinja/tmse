#include "fillerbox.h"
#include "utils/terminalutils.h"

namespace Widgets
{

FillerBox::FillerBox(const Term::Color& color) :
    mColor{color}
{
}

void FillerBox::widgetDraw(Term::Window& window)
{
    Utils::fillBGFG(window, mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, mColor, mColor);
}



}
