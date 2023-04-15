
#include "waitkey.h"
#include <cpp-terminal/input.hpp>

using namespace Olagarro::Tasks;

namespace TMSETasks
{

WaitKey::WaitKey(Term::Key::Value key, MainWindow& mainWindow) :
    mKey{key},
    mMainWindow{mainWindow}
{
}

Olagarro::Tasks::Task::State WaitKey::taskUpdate(float deltaTime)
{
    if(mMainWindow.currentKey() == mKey)
    {
        mMainWindow.consumeCurrentKey();
        return Task::State::Finished;
    }

    return Task::State::Working;
}

Olagarro::Tasks::TaskUP waitKey(Term::Key::Value key, MainWindow& mainWindow)
{
    return std::make_unique<WaitKey>(key, mainWindow);
}

}
