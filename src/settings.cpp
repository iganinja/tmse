#include "settings.h"

static Settings settingsStorage{};

using Color = Term::Color::Name;

void loadSettings()
{
    settingsStorage.mainMenuColors = ColorSetting{Color::Blue, Color::Blue};

    settingsStorage.welcomeBackgroundColors = ColorSetting{Color::Gray, Color::Black};

    settingsStorage.menuItemColors = ColorSetting{Color::Blue, Color::BrightYellow};

    settingsStorage.selectedMenuItemColors = ColorSetting{Color::Yellow, Color::BrightBlue};

    settingsStorage.menuItemCurrentItemColors = settingsStorage.menuItemColors;

    settingsStorage.filesTabsColors = ColorSetting{Color::White, Color::Gray};
}

const Settings& settings()
{
    return settingsStorage;
}
