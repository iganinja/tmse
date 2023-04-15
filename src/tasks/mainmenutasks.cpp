#include "mainmenutasks.h"

using namespace Olagarro::Tasks;

namespace TMSETasks
{

TaskUP mainMenu(Widgets::MainMenu& mainMenu)
{
    return wait(1.0f);
}

}

