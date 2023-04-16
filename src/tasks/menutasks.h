#pragma once

#include "tasks/task.h"
#include "mainwindow.h"
#include "widgets/menu.h"

#include <functional>

namespace TMSETasks
{

Olagarro::Tasks::TaskUP menuNavigationTasks(MainWindow& mainWindow, Widgets::Menu& menu);
Olagarro::Tasks::TaskUP menuNavigationTasks(MainWindow& mainWindow, std::function<Widgets::Menu& ()> menuProvider);

}
