#pragma once

#include "tasks/task.h"

namespace TMSETasks
{

template<typename Event, typename EventHandler>
class WaitEvent : public Olagarro::Tasks::Task
{
public:
    WaitEvent(Event& event, EventHandler eventHandler) :
        mEvent{event},
        mEventHandler{eventHandler}
    {
    }

private:
    State taskUpdate(float deltaTime) override
    {
        if(mEvent)
        {
            mEventHandler(mEvent);
            return State::Finished;
        }

        return State::Working;
    }

    Event& mEvent;
    EventHandler mEventHandler;
};

template<typename Event, typename EventHandler>
Olagarro::Tasks::TaskUP waitEvent(Event& event, EventHandler eventHandler)
{
    return std::make_unique<WaitEvent<Event, EventHandler>>(event, eventHandler);
}

}
