#include "mainwindowtasks.h"
#include "tasks/waitevent.h"
#include "tasks/serial.h"
#include "tasks/repeat.h"

using namespace Olagarro::Tasks;

namespace TMSETasks
{

Olagarro::Tasks::TaskUP mainWindowTasks(MainWindow& mainWindow)
{
    return repeatForever(
            serial(
                waitEvent(mainWindow.mainMenu().exitApp,
                [&](const auto& event)
                {
                    mainWindow.exit();
                })
            )
        );
}

}
