#include "mainwindow.h"

namespace Widgets
{

MainWindow::MainWindow() :
    mFillerBox{Term::Color::Name::Red}
{

}

void MainWindow::widgetDraw(Term::Window& window)
{
    mFillerBox.draw(window);
}

void MainWindow::widgetOnResize(std::size_t newWidth, std::size_t newHeight)
{
    mFillerBox.onResize(newWidth, newHeight);
}



}
