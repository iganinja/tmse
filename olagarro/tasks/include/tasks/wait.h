#ifndef WAIT_H
#define WAIT_H

#include "tasks/task.h"

namespace Olagarro
{
namespace Tasks
{

TaskUP wait(float waitTime);

template<typename Predicate>
class WaitPredicate : public Task
{
public:
    WaitPredicate(Predicate predicate) :
        Task{"WaitCallable"},
        mPredicate{predicate}
    {
    }

    State taskUpdate(float deltaTime) override
    {
        return mPredicate()? State::Finished : State::Working;
    }

private:
    Predicate mPredicate;
};

template<typename Predicate>
TaskUP wait(Predicate predicate)
{
    return std::make_unique<WaitPredicate<Predicate>>(predicate);
}

}
}

#endif // WAIT_H
