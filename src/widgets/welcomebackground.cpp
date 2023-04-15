#include "welcomebackground.h"
#include "settings.h"
#include "utils/terminalutils.h"
#include "localization.h"

namespace Widgets
{

void WelcomeBackground::widgetDraw(Term::Window& window)
{
    const auto& colors{settings().welcomeBackgroundColors};

    Utils::fillBGFG(window, mPosition.x(), mPosition.y(), mPosition.x() + mSize.x() - 1, mPosition.y() + mSize.y() - 1, colors.background, colors.foreground);

    //write(0, 0, "hola qué tal", HorizontalAnchor::Left, Term::Color::Name::Red, Term::Color::Name::BrightWhite, window);

    const std::vector<std::string> CenteredTexts
    {
        tr("Welcome to Text Mode Sane Editor!"),
        tr("version 0.1"),
        tr(""),
        tr("Some keyboard shortcuts:")
    };

    const std::vector<std::string> ShortcutTexts
    {
        tr(" F4: toggle main menu"),
        tr("F12: exit")
    };

    auto printText = [this, &window](int offsetXFromCenter, int baseY, const std::vector<std::string>& textList, HorizontalAnchor anchor)
    {
        for(const auto& text : textList)
        {
            write(size().x() / 2 + offsetXFromCenter, baseY, text, anchor, Term::Color::Name::Red, Term::Color::Name::BrightWhite, window);
            baseY += 1;
        }

        return baseY;
    };

    auto baseY{static_cast<int>(size().y() * 0.25f)};

    baseY = printText(0, baseY, CenteredTexts, HorizontalAnchor::Center);
    printText(-10, baseY, ShortcutTexts, HorizontalAnchor::Left);
}


}
