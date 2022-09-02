#ifndef UNDOREDOSTACK_H
#define UNDOREDOSTACK_H

#include "command.h"

#include <stack>
#include <memory>

namespace TMSE
{

using CommandUP = std::unique_ptr<Command>;

class UndoRedoStack
{
public:
    void push(CommandUP&& command);
    void undo();
    void redo();

    bool isDirty() const;
    void clearDirty();

private:
    std::stack<CommandUP> mUndoStack;
    std::stack<CommandUP> mRedoStack;
    bool mIsDirty = false;
};

}

#endif // UNDOREDOSTACK_H
