#pragma once

#include "tasks/task.h"
#include "mainwindow.h"

#include <cpp-terminal/key.hpp>


namespace TMSETasks
{

class WaitKey : public Olagarro::Tasks::Task
{
public:
    WaitKey(Term::Key::Value key, MainWindow& mainWindow);

private:
    State taskUpdate(float deltaTime) override;

    Term::Key::Value mKey;
    MainWindow& mMainWindow;
};

Olagarro::Tasks::TaskUP waitKey(Term::Key::Value key, MainWindow& mainWindow);

}
