#include "settings.h"

static Settings settingsStorage{};

using Color = Term::Color::Name;

void loadSettings()
{
    settingsStorage.mainMenuColor = ColorSetting{Color::BrightMagenta, Color::BrightMagenta};

    settingsStorage.menuItemColor = ColorSetting{Color::Blue, Color::BrightYellow};

    settingsStorage.selectedMenuItemColor = ColorSetting{Color::Yellow, Color::BrightBlue};

    settingsStorage.menuItemCurrentItemColor = settingsStorage.menuItemColor;
}

const Settings& settings()
{
    return settingsStorage;
}
