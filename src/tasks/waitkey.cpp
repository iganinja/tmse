
#include "waitkey.h"
#include <cpp-terminal/input.hpp>

using namespace Olagarro::Tasks;

namespace TMSETasks
{

WaitKey::WaitKey(Term::Key::Value key) :
    mKey{key}
{
}

Olagarro::Tasks::Task::State WaitKey::taskUpdate(float deltaTime)
{
    auto keyEvent{Term::Platform::read_raw()};

    if(!keyEvent.empty() && mKey == Term::Key{keyEvent})
    {
        return Task::State::Finished;
    }

    return Task::State::Working;
}

}
