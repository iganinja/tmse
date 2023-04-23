#pragma once

#include "tasks/taskexecutor.h"
#include "widgets/mainmenu.h"
#include "widgets/filestabs.h"
#include "widgets/textbox.h"

#include <cpp-terminal/terminal.hpp>
#include <cpp-terminal/input.hpp>
#include <memory>

class MainWindow
{
public:
    MainWindow();

    void run();

    Term::Key currentKey() const;
    void consumeCurrentKey();

    void exit();

    Widgets::MainMenu& mainMenu();

    void toggleMainMenuVisibility();

    void toggleWelcomeBackgroundVisibility();

    void enableModal();
    void disableModal();

private:
    void draw();
    void onResize(size_t newWidth, size_t newHeight);
    void checkTerminalResizing();

    void createTasks();

    Widgets::MainMenu mMainMenu;
    Widgets::FilesTabs mFilesTabs;
    Widgets::TextBox testingTextBox;

    Olagarro::Tasks::TaskExecutor mTaskExecutor;

    Term::Terminal mTerminal;
    std::unique_ptr<Term::Window> mTerminalWindow;
    bool mShouldKeepRunning{true};
    Utils::Size mLastTerminalSize;

    Term::Key mCurrentKey{Term::Key::NO_KEY};
    bool mIsModal{false};
};

