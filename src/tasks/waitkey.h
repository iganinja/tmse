#pragma once

#include <tasks/task.h>
#include <cpp-terminal/key.hpp>


namespace TMSETasks
{

class WaitKey : public Olagarro::Tasks::Task
{
public:
    WaitKey(Term::Key::Value key);

private:
    State taskUpdate(float deltaTime) override;

    Term::Key::Value mKey;
};

}
