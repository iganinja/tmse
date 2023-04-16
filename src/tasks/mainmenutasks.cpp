#include "mainmenutasks.h"
#include "tasks/execute.h"
#include "tasks/serial.h"
#include "tasks/earlyexitparallel.h"
#include "tasks/repeat.h"
#include "tasks/wait.h"
#include "waitkey.h"
#include "tasksutils.h"
#include "menutasks.h"

using namespace Olagarro::Tasks;
using namespace Term;

namespace TMSETasks
{

TaskUP menuNavigation(MainWindow& mainWindow)
{
    auto& mainMenu{mainWindow.mainMenu()};

    return serial(
                wait([&]()
                {
                    return mainMenu.isVisible();
                }),
                earlyExitParallel(
                    waitKey(Key::ARROW_LEFT, mainWindow,
                    [&]()
                    {
                        if(mainMenu.currentMenuIndex() == 0)
                        {
                            mainMenu.showMenu(mainMenu.menuNumber() - 1);
                        }
                        else
                        {
                            mainMenu.showMenu(mainMenu.currentMenuIndex() - 1);
                        }
                    }),
                    waitKey(Key::ARROW_RIGHT, mainWindow,
                    [&]()
                    {
                        if(mainMenu.currentMenuIndex() == mainMenu.menuNumber() - 1)
                        {
                            mainMenu.showMenu(0);
                        }
                        else
                        {
                            mainMenu.showMenu(mainMenu.currentMenuIndex() + 1);
                        }
                    }),
                    menuNavigationTasks(mainWindow, [&]() -> Widgets::Menu&
                    {
                        return mainMenu.currentMenu();
                    })
                )
            );
}

TaskUP mainMenu(MainWindow& mainWindow)
{
    return repeatForever(
            earlyExitParallel(
                waitKey(Key::F12, mainWindow,
                [&]()
                {
                    mainWindow.exit();
                }),
                waitKey(Key::F4, mainWindow,
                [&]()
                {
                    mainWindow.toggleMainMenuVisibility();

                    auto& mainMenu{mainWindow.mainMenu()};

                    if(mainMenu.isVisible())
                    {
                        mainMenu.showMenu(0);
                    }
                }),
                menuNavigation(mainWindow)
            )
        );
}

}

