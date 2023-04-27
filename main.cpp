#include <cpp-terminal/exception.hpp>
#include <cpp-terminal/input.hpp>
#include <cpp-terminal/terminal.hpp>
#include <cpp-terminal/tty.hpp>
#include <cpp-terminal/window.hpp>
#include <cpp-terminal/options.hpp>

#include "settings.h"
#include "mainwindow.h"
#include "utils/exception.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main()
{
    try
    {
        if(!Term::is_stdin_a_tty())
        {
            std::cout << "The terminal is not attached to a TTY and therefore can't catch user input. Exiting...\n";
            return 1;
        }

        loadSettings();

        MainWindow mainWindow;

        mainWindow.run();
    }
    catch(Utils::Exception& exception)
    {
        std::cout << "Error: " << exception.message() << "\n";
        return 1;
    }
    catch(const Term::Exception& exception)
    {
        std::cout << "cpp-terminal error: " << exception.what() << "\n";
        return 2;
    }
    catch(const std::exception& exception)
    {
        std::cout << "Unknown error: " << exception.what() << "\n";
        return 3;
    }

    return 0;
}
