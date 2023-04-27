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
    mTerminal{{Term::Options::Option::ClearScreen, Term::Options::Option::NoCursor, Term::Options::Option::NoSignalKeys}},
    testingSelectionWindow{"About", "Text Mode Sane Editor v0.1", {"OK"}, 40, 1, 1}
{
    Term::terminal_title("Text Mode Sane Editor");

    checkTerminalResizing();

    std::string text
    {
        "Esto es una prueba de un texto que tiene que partirse pero al nivel de las palabras, no a nivel de carácteres."
    };

    testingTextBox.setTitle("Warning");
    testingTextBox.setText(std::move(text));

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

        std::this_thread::sleep_for(1ms);

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

    // WARNING Temporal
    if(mSize.x <= 40 || mSize.y < 10)
    {
        return;
    }

    mFilesTabs.draw(*mTerminalWindow);
    mMainMenu.draw(*mTerminalWindow);
    testingSelectionWindow.draw(*mTerminalWindow);
    testingTextBox.draw(*mTerminalWindow);

    std::cout << mTerminalWindow->render(1, 1, true) << std::flush;
}

void MainWindow::onResize(size_t newWidth, size_t newHeight)
{
    mSize = Utils::Size{newWidth, newHeight};

    if(mMainMenu.isVisible())
    {
        mMainMenu.setPosition(0, 0);
        mMainMenu.onResize(newWidth, 1);

        mFilesTabs.setPosition(0, 1);
        mFilesTabs.onResize(newWidth, newHeight - 1);

        testingSelectionWindow.setPosition(1, 2);
    }
    else
    {
        mFilesTabs.setPosition(0, 0);
        mFilesTabs.onResize(newWidth, newHeight);

        testingSelectionWindow.setPosition(1, 1);
    }

    testingTextBox.setPosition(10, 20);
    testingTextBox.onResize(newWidth * 0.8, 6);
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
