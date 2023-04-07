#ifndef REPEAT_H
#define REPEAT_H

#include "tasks/task.h"

namespace Olagarro
{
namespace Tasks
{

template<typename Predicate>
class RepeatWhile : public Task
{
public:
    RepeatWhile(TaskUP&& task, Predicate predicate) :
        mTask{std::move(task)}, mPredicate{predicate}
    {
    }

    std::vector<const Task*> children() const override
    {
        return {mTask.get()};
    }

    std::vector<std::unique_ptr<Task>> grabChildren() override
    {
        std::vector<std::unique_ptr<Task>> children;

        children.emplace_back(std::move(mTask));

        return children;
    }

protected:
    void taskOnAboutToStart() override
    {
        mTask->onAboutToStart();
    }

    State taskUpdate(float deltaTime) override
    {
        const auto result = mTask->update(deltaTime);

        if(result == State::Finished)
        {
            if(!mPredicate())
            {
                return State::Finished;
            }

            mTask->onAboutToStart();
        }

        return State::Working;
    }

private:
    TaskUP mTask;
    Predicate mPredicate;
};

TaskUP repeat(TaskUP&& task, size_t times);
TaskUP repeatForever(TaskUP&& task);



template<typename Predicate>
TaskUP repeatWhile(TaskUP&& task, Predicate predicate)
{
    return std::make_unique<RepeatWhile<Predicate>>(std::move(task), predicate);
}

}
}


#endif // REPEAT_H
