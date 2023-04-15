#include "mainwindow.h"
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

    while(mShouldKeepRunning)
    {
        auto keyEvent{Term::Platform::read_raw()};

        mCurrentKey = Term::Key::NO_KEY;

        if(!keyEvent.empty())
        {
            mCurrentKey = Term::Key{keyEvent};

            mTaskExecutor.update();

            draw();
        }

        std::this_thread::sleep_for(100ms);

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

    if(mMainMenu.isVisible())
    {
        mWelcomeBackground.setPosition(Utils::Position{1, 2});
        mWelcomeBackground.onResize(mLastTerminalSize.x(), mLastTerminalSize.y() - 1);
    }
    else
    {
        mWelcomeBackground.setPosition(Utils::Position{1, 1});
        mWelcomeBackground.onResize(mLastTerminalSize.x(), mLastTerminalSize.y());
    }

    draw();
}

void MainWindow::draw()
{
    mTerminalWindow->clear();

    mWelcomeBackground.draw(*mTerminalWindow);
    mMainMenu.draw(*mTerminalWindow);

    std::cout << mTerminalWindow->render(1, 1, true) << std::flush;
}

void MainWindow::onResize(size_t newWidth, size_t newHeight)
{
    mMainMenu.setPosition(Utils::Position{1, 1});
    mMainMenu.onResize(newWidth, 1);

    mWelcomeBackground.setPosition(Utils::Position{1, 2});
    mWelcomeBackground.onResize(newWidth, newHeight - 1);
}

void MainWindow::checkTerminalResizing()
{
    auto currentTerminalSize{Term::screen_size()};
    const Utils::Size currentSize{currentTerminalSize.columns(), currentTerminalSize.rows()};

    if(mLastTerminalSize != currentSize)
    {
        mTerminalWindow = std::make_unique<Term::Window>(currentSize.x(), currentSize.y());
        onResize(currentSize.x(), currentSize.y());
        mLastTerminalSize = currentSize;
    }
}

void MainWindow::createTasks()
{
    mTaskExecutor.addTask(TMSETasks::mainMenu(*this));
}
