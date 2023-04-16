#include "settings.h"

static Settings settingsStorage{};

using Color = Term::Color::Name;

void loadSettings()
{
    settingsStorage.mainMenuColors = ColorSetting{Color::Blue, Color::Blue};

    settingsStorage.menuItemColors = ColorSetting{Color::Blue, Color::BrightYellow};

    settingsStorage.selectedMenuItemColors = ColorSetting{Color::Yellow, Color::BrightBlue};

    settingsStorage.menuItemCurrentItemColors = settingsStorage.menuItemColors;

    settingsStorage.welcomeBackgroundColors = ColorSetting{Color::Gray, Color::Black};
}

const Settings& settings()
{
    return settingsStorage;
}
