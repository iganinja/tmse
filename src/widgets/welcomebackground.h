#pragma once

#include "widget.h"

namespace Widgets
{

class WelcomeBackground : public Widget
{
public:

private:
    void widgetDraw(Term::Window& window) override;
};

}
