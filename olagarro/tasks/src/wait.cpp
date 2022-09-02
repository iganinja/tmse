#include "tasks/wait.h"

namespace Olagarro
{
namespace Tasks
{

class Wait : public Task
{
public:
    Wait(float waitTime) :
        Task{"Wait"},
        mWaitTime{waitTime}
    {
    }

    void taskOnAboutToStart() override
    {
        mWaitedTime = 0;
    }

    State taskUpdate(float deltaTime) override
    {
        mWaitedTime += deltaTime;

        return mWaitedTime >= mWaitTime? State::Finished : State::Working;
    }

private:
    const float mWaitTime;
    float mWaitedTime;
};

TaskUP wait(float waitTime)
{
    return std::make_unique<Wait>(waitTime);
}

}
}
