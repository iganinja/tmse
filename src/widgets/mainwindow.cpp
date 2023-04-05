#include "mainwindow.h"

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

void MainWindow::widgetOnResize(std::size_t newWidth, std::size_t newHeight)
{
    mMainMenu.setPosition(Utils::Position{1, 1});
    mMainMenu.onResize(newWidth, 1);

    mFillerBox.setPosition(Utils::Position{1, 2});
    mFillerBox.onResize(newWidth, newHeight - 1);
}



}
