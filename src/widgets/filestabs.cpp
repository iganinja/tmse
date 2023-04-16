#include "filestabs.h"
#include "settings.h"

namespace Widgets
{

void FilesTabs::widgetDraw(Term::Window& window)
{
    drawRect(0, 0, size().x(), size().y(), settings().filesTabsColors, window);

    write(0, 0, " test.txt | jarl.cpp | my_script.sh | another_file.lua", HorizontalAnchor::Left, window);
}

}
