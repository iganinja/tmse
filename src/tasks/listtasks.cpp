#include "listtasks.h"
#include "tasksutils.h"
#include "tasks/earlyexitparallel.h"
#include "tasks/repeat.h"

#include <cpp-terminal/input.hpp>

namespace TMSETasks
{

using namespace Olagarro::Tasks;
using namespace Term;

Olagarro::Tasks::TaskUP listTasks(MainWindow& mainWindow, Widgets::List& list)
{
    return repeatForever(
            earlyExitParallel(
                waitKey(Key::ARROW_UP, mainWindow,
                        [&]()
                        {
                            list.selectPreviousElement();
                        }),
                waitKey(Key::ARROW_DOWN, mainWindow,
                        [&]()
                        {
                            list.selectNextElement();
                        })
                )
        );
}

}
