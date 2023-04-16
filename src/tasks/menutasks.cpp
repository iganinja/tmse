#include "menutasks.h"
#include "tasks/earlyexitparallel.h"
#include "tasksutils.h"

#include <cpp-terminal/input.hpp>

namespace TMSETasks
{

using namespace Olagarro::Tasks;
using namespace Term;

TaskUP menuNavigationTasks(MainWindow& mainWindow, Widgets::Menu& menu)
{
    return menuNavigationTasks(mainWindow, [&]() -> Widgets::Menu&
    {
        return menu;
    });
}

TaskUP menuNavigationTasks(MainWindow& mainWindow, std::function<Widgets::Menu& ()> menuProvider)
{
    return earlyExitParallel(
        waitKey(Key::ARROW_UP, mainWindow,
        [&, menuProvider]()
        {
            auto& menu{menuProvider()};

            if(menu.selectedEntry() == 0)
            {
                menu.setSelectedEntry(menu.entries().size() - 1);
            }
            else
            {
                menu.setSelectedEntry(menu.selectedEntry() - 1);
            }
        }),
        waitKey(Key::ARROW_DOWN, mainWindow,
        [&, menuProvider]()
        {
            auto& menu{menuProvider()};

            if(menu.selectedEntry() == menu.entries().size() - 1)
            {
                menu.setSelectedEntry(0);
            }
            else
            {
                menu.setSelectedEntry(menu.selectedEntry() + 1);
            }
        }),
        waitKey(Key::ENTER, mainWindow,
        [&, menuProvider]()
        {
            auto& menu{menuProvider()};

            menu.triggerSelectedEntry();
        })
    );
}

}
