#include "terminalutils.h"

namespace Utils
{

void fillBGFG(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const Term::Color& colorBG, const Term::Color& colorFG)
{
    window.fill_bg(x1, y1, x2, y2, colorBG);
    window.fill_fg(x1, y1, x2, y2, colorFG);
}

void drawRect(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const Term::Color& colorBG, const Term::Color& colorFG)
{
    fillBGFG(window, x1, y1, x2, y2, colorBG, colorFG);
    window.print_rect(x1, y1, x2, y2);
}

void fillBGFG(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const ColorSetting& colorSetting)
{
    fillBGFG(window, x1, y1, x2, y2, colorSetting.background, colorSetting.foreground);
}

void drawRect(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const ColorSetting& colorSetting)
{
    drawRect(window, x1, y1, x2, y2, colorSetting.background, colorSetting.foreground);
}


}
