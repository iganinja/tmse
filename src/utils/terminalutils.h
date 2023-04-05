#pragma once

#include <cpp-terminal/color.hpp>
#include <cpp-terminal/window.hpp>

#include "settings.h"

namespace Utils
{

void fillBGFG(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const Term::Color& colorBG, const Term::Color& colorFG);
void drawRect(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const Term::Color& colorBG, const Term::Color& colorFG);

void fillBGFG(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const ColorSetting& colorSetting);
void drawRect(Term::Window& window, std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, const ColorSetting& colorSetting);

}
