#include "tasks/select.h"

namespace Olagarro
{
namespace Tasks
{

class Select : public Task
{
public:
    Select(std::vector<TaskPair>&& taskPairs) :
        Task{"Select"}
    {
        for(auto& pair : taskPairs)
        {
            if(not pair.first or not pair.second)
            {
                continue;
            }

            mTaskPairs.push_back(std::move(pair));
        }
    }

    void taskOnAboutToStart() override
    {
        mCurrentTask = nullptr;

        for(auto& pair : mTaskPairs)
        {
            pair.first->onAboutToStart();
        }
    }

    State taskUpdate(float deltaTime) override
    {
        if(mCurrentTask)
        {
            return mCurrentTask->update(deltaTime);
        }

        for(auto& pair : mTaskPairs)
        {
            if(pair.first->update(deltaTime) == State::Finished)
            {
                mCurrentTask = pair.second.get();
                mCurrentTask->onAboutToStart();
            }
        }

        return State::Working;
    }

private:
    std::vector<TaskPair> mTaskPairs;
    Task* mCurrentTask = nullptr;
};

TaskUP makeSelect(std::vector<TaskPair>&& taskPairs)
{

}

}
}
