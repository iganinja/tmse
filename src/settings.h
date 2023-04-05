#pragma once

#include <cpp-terminal/color.hpp>

struct ColorSetting
{
    Term::Color background;
    Term::Color foreground;
};

struct Settings
{
    ColorSetting mainMenuColor;

    ColorSetting menuItemColor;
    ColorSetting selectedMenuItemColor;
    ColorSetting menuItemCurrentItemColor;
};

void loadSettings();
const Settings& settings();
