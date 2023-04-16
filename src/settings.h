#pragma once

#include <cpp-terminal/color.hpp>

struct ColorSetting
{
    Term::Color background;
    Term::Color foreground;
};

struct Settings
{
    ColorSetting mainMenuColors;
    ColorSetting welcomeBackgroundColors;

    ColorSetting menuItemColors;
    ColorSetting selectedMenuItemColors;
    ColorSetting menuItemCurrentItemColors;
    ColorSetting filesTabsColors;
};

void loadSettings();
const Settings& settings();
