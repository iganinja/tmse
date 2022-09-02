#include "command.h"

namespace TMSE
{

Command::Command(const std::string &name) :
    mName{name}
{
}

const std::string& Command::name() const
{
    return mName;
}

bool Command::merge(Command& command)
{
    return false;
}


}
