#pragma once

#include "tasks/task.h"
#include "mainwindow.h"
#include "widgets/list.h"

namespace TMSETasks
{

Olagarro::Tasks::TaskUP listTasks(MainWindow& mainWindow, Widgets::List& list);

}
