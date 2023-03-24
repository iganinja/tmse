#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "commands/undoredostack.h"
#include "document.h"
#include "view.h"

#include <tasks/taskexecutor.h>

#include <cpp-terminal/base.hpp>
#include <cpp-terminal/input.hpp>
#include <cpp-terminal/window.hpp>
#include <cpp-terminal/terminal.hpp>


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
    bool mKeepRunning{true};

    UndoRedoStack mUndoRedoStack;
    Document mDocument;
    View mView;

    Term::Terminal mTerminal{true, true, false};
    std::unique_ptr<Term::Window> mTerminalWindow;
};

}

#endif // TEXTEDITOR_H
