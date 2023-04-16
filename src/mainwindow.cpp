#include "mainwindow.h"
#include "tasks/mainwindowtasks.h"
#include "tasks/mainmenutasks.h"

#include <cpp-terminal/terminal.hpp>
#include <thread>
#include <iostream>

using namespace Olagarro::Tasks;
using namespace TMSETasks;
using namespace std::chrono_literals;

MainWindow::MainWindow() :
    mTerminal{{Term::Options::Option::ClearScreen, Term::Options::Option::Cursor, Term::Options::Option::NoSignalKeys}}
{
    Term::terminal_title("Text Mode Sane Editor");

    checkTerminalResizing();

    toggleMainMenuVisibility();
}

void MainWindow::run()
{
    createTasks();

    draw();

    auto shouldRedraw{true};

    while(mShouldKeepRunning)
    {
        auto keyEvent{Term::Platform::read_raw()};

        mCurrentKey = Term::Key::NO_KEY;

        if(!keyEvent.empty())
        {
            mCurrentKey = Term::Key{keyEvent};
            shouldRedraw = true;
        }
        else
        {
            shouldRedraw = false;
        }

        mTaskExecutor.update();

        if(shouldRedraw)
        {
            draw();
        }

        std::this_thread::sleep_for(50ms);

        checkTerminalResizing();
    }
}

Term::Key MainWindow::currentKey() const
{
    return mCurrentKey;
}

void MainWindow::consumeCurrentKey()
{
    mCurrentKey = Term::Key::NO_KEY;
}

void MainWindow::exit()
{
    mShouldKeepRunning = false;
}

Widgets::MainMenu& MainWindow::mainMenu()
{
    return mMainMenu;
}

void MainWindow::toggleMainMenuVisibility()
{
    mMainMenu.setVisible(!mMainMenu.isVisible());
    onResize(mLastTerminalSize.x, mLastTerminalSize.y);
    draw();
}

void MainWindow::toggleWelcomeBackgroundVisibility()
{
    onResize(mLastTerminalSize.x, mLastTerminalSize.y);
    draw();
}

void MainWindow::draw()
{
    mTerminalWindow->clear();

    mFilesTabs.draw(*mTerminalWindow);
    mMainMenu.draw(*mTerminalWindow);

    std::cout << mTerminalWindow->render(1, 1, true) << std::flush;
}

void MainWindow::onResize(size_t newWidth, size_t newHeight)
{
    if(mMainMenu.isVisible())
    {
        mMainMenu.setPosition(0, 0);
        mMainMenu.onResize(newWidth, 1);

        mFilesTabs.setPosition(0, 1);
        mFilesTabs.onResize(newWidth, newHeight - 1);
    }
    else
    {
        mFilesTabs.setPosition(0, 0);
        mFilesTabs.onResize(newWidth, newHeight);
    }
}

void MainWindow::checkTerminalResizing()
{
    auto currentTerminalSize{Term::screen_size()};
    const Utils::Size currentSize{currentTerminalSize.columns(), currentTerminalSize.rows()};

    if(mLastTerminalSize != currentSize)
    {
        mTerminalWindow = std::make_unique<Term::Window>(currentSize.x, currentSize.y);
        onResize(currentSize.x, currentSize.y);
        mLastTerminalSize = currentSize;
    }
}

void MainWindow::createTasks()
{
    mTaskExecutor.addTask(TMSETasks::mainWindowTasks(*this));
    mTaskExecutor.addTask(TMSETasks::mainMenu(*this));
}
