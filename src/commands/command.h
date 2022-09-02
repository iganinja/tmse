#ifndef COMMAND_H
#define COMMAND_H

#include <string>

namespace TMSE
{

class Command
{
public:
    ~Command() = default;

    Command(const std::string& name);

    const std::string& name() const;

    virtual bool merge(Command& command);

    virtual void redo() = 0;

    virtual void undo() = 0;

private:
    const std::string mName;
};

}

#endif // COMMAND_H
