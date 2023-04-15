#include "mainwindow.h"
#include "tasks/mainmenutasks.h"

#include <cpp-terminal/input.hpp>

using namespace Olagarro::Tasks;
using namespace TMSETasks;

namespace Widgets
{

MainWindow::MainWindow() :
    mFillerBox{Term::Color::Name::Gray}
{
}

void MainWindow::widgetDraw(Term::Window& window)
{
    mFillerBox.draw(window);
    mMainMenu.draw(window);
}

void MainWindow::widgetOnResize(size_t newWidth, size_t newHeight)
{
    mMainMenu.setPosition(Utils::Position{1, 1});
    mMainMenu.onResize(newWidth, 1);

    mFillerBox.setPosition(Utils::Position{1, 2});
    mFillerBox.onResize(newWidth, newHeight - 1);
}

void MainWindow::onKey(int32_t key)
{
//    if(key == Term::Key::F4)
//    {
//        return;
//    }
}

void MainWindow::createTasks()
{
    mTaskExecutor.addTask(mainMenu(mMainMenu));
}



}
