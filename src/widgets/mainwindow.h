#pragma once

#include "widget.h"
#include "fillerbox.h"
#include "mainmenu.h"
#include <tasks/taskexecutor.h>

#include <memory>

namespace Widgets
{

class MainWindow : public Widget
{
public:
    MainWindow();

    void onKey(std::int32_t key);

private:
    void widgetDraw(Term::Window& window) override;
    void widgetOnResize(size_t newWidth, size_t newHeight) override;

    void createTasks();

    MainMenu mMainMenu;
    FillerBox mFillerBox;

    Olagarro::Tasks::TaskExecutor mTaskExecutor;
};

}
