#ifndef SELECT_H
#define SELECT_H

#include "tasks/task.h"

namespace Olagarro
{
namespace Tasks
{

using TaskPair = std::pair<TaskUP, TaskUP>;

TaskUP makeSelect(std::vector<TaskPair>&& taskPairs);

template<typename... TaskPairs>
TaskUP select(TaskPairs&&... taskPairs)
{
    TaskUP tasksArray[] = {std::move(taskPairs)...};
    return makeSelect(std::vector<TaskPair>{std::make_move_iterator(std::begin(tasksArray)), std::make_move_iterator(std::end(tasksArray))});
}

}
}

#endif // SELECT_H
