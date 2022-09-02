#include "undoredostack.h"

namespace TMSE
{


void UndoRedoStack::push(CommandUP&& command)
{
    mUndoStack = std::stack<CommandUP>{};

    command->redo();

    mRedoStack.push(std::move(command));

    mIsDirty = true;
}

void UndoRedoStack::undo()
{
    if(mRedoStack.empty())
    {
        return;
    }

    auto command{std::move(mRedoStack.top())};
    mRedoStack.pop();

    command->undo();

    mUndoStack.push(std::move(command));

    mIsDirty = true;
}

void UndoRedoStack::redo()
{
    if(mUndoStack.empty())
    {
        return;
    }

    auto command{std::move(mUndoStack.top())};
    mUndoStack.pop();

    push(std::move(command));
}

bool UndoRedoStack::isDirty() const
{
    return mIsDirty;
}

void UndoRedoStack::clearDirty()
{
    mIsDirty = false;
}

}
