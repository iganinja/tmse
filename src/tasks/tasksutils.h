#pragma once

#include <cpp-terminal/input.hpp>

#include "tasks/taskscore.h"
#include "mainwindow.h"
#include "waitkey.h"

namespace TMSETasks
{

template<typename Functor>
Olagarro::Tasks::TaskUP waitKey(Term::Key::Value key, MainWindow& mainWindow, Functor functor)
{
    return serial(
                waitKey(key, mainWindow),
                Olagarro::Tasks::execute(functor)
            );
}

}
