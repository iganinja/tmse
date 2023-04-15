#ifndef TASKEXECUTOR_H
#define TASKEXECUTOR_H

#include "task.h"

#include <chrono>
#include <memory>
#include <vector>

namespace Olagarro
{
namespace Tasks
{

class TaskExecutor
{
public:
    void addTask(TaskUP&& task);

    void update();

private:
    std::vector<TaskUP> mTasks;

    using Clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<Clock> mLastTimePoint;
};

}
}

#endif // TASKEXECUTOR_H
