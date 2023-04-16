#include "fillerbox.h"

namespace Widgets
{

FillerBox::FillerBox(const Term::Color& color) :
    mColor{color}
{
}

void FillerBox::widgetDraw(Term::Window& window)
{
    drawRect(0, 0, size().x, size().y, mColor, mColor, window);
}



}
