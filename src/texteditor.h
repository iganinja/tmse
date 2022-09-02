#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "commands/undoredostack.h"

#include <tasks/taskexecutor.h>


namespace TMSE
{

class TextEditor
{
public:
    TextEditor();

    bool run();

private:
    Olagarro::Tasks::TaskExecutor mExecutor;
    bool mKeepRunning = true;

    UndoRedoStack mUndoRedoStack;
};

}

#endif // TEXTEDITOR_H
