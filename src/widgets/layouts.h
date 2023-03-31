#pragma once

#include <vector>

#include "widget.h"

namespace Widgets
{

class VerticalLayout : public Widget
{
public:
    VerticalLayout(std::initializer_list<WidgetUP>&& widgets);

    void addWidget(WidgetUP&& widget);

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(std::size_t newWidth, std::size_t newHeight) override;

    std::vector<WidgetUP> mWidgets;
};

}
