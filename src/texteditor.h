#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "commands/undoredostack.h"
#include "document.h"

#include <tasks/taskexecutor.h>


namespace TMSE
{

class TextEditor
{
public:
    TextEditor();

    bool run();

private:
    void createTasks();

    Olagarro::Tasks::TaskExecutor mExecutor;
    bool mKeepRunning = true;

    UndoRedoStack mUndoRedoStack;
    Document document;
};

}

#endif // TEXTEDITOR_H
