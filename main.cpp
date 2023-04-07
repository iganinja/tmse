#include "cpp-terminal/base.hpp"
#include "cpp-terminal/exception.hpp"
#include "cpp-terminal/input.hpp"
#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/tty.hpp"
#include "cpp-terminal/window.hpp"
#include "cpp-terminal/options.hpp"

#include "settings.h"
#include "widgets/mainwindow.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

std::string render(Term::Window& screen, const std::size_t& rows, const std::size_t& cols, const std::size_t& menuheight, const std::size_t& menuwidth, const std::size_t& menupos)
{
    screen.clear();
//    std::size_t menux0 = (cols - menuwidth) / 2 + 1;
//    std::size_t menuy0 = (rows - menuheight) / 2 + 1;
//    screen.print_rect(menux0, menuy0, menux0 + menuwidth + 1, menuy0 + menuheight + 1);

//    for(std::size_t i = 1; i <= menuheight; i++)
//    {
//        std::string s = std::to_string(i) + ": item";
//        screen.print_str(menux0 + 1, menuy0 + i, s);
//        if(i == menupos)
//        {
//            screen.fill_fg(menux0 + 1, menuy0 + i, menux0 + s.size(), menuy0 + i, Term::Color::Name::Red);    // FG
//            screen.fill_bg(menux0 + 1, menuy0 + i, menux0 + menuwidth, menuy0 + i, Term::Color::Name::Gray);  // BG
//            screen.fill_style(menux0 + 1, menuy0 + i, menux0 + s.size(), menuy0 + i, Term::Style::BOLD);
//        }
//        else
//        {
//            screen.fill_fg(menux0 + 1, menuy0 + i, menux0 + s.size(), menuy0 + i, Term::Color::Name::Blue);
//            screen.fill_bg(menux0 + 1, menuy0 + i, menux0 + menuwidth, menuy0 + i, Term::Color::Name::Green);
//        }
//    }

//    std::size_t y = menuy0 + menuheight + 5;
//    screen.print_str(1, y, "Selected item: " + std::to_string(menupos));
//    screen.print_str(1, y + 1, "Menu width: " + std::to_string(menuwidth));
//    screen.print_str(1, y + 2, "Menu height: " + std::to_string(menuheight));
//    screen.print_str(1, y + 3, "Unicode test: Ondřej Čertík, ἐξήκοι");

    screen.fill_bg(1, 1, 20, 4, Term::Color::Name::Blue);
    screen.fill_fg(1, 1, 20, 4, Term::Color::Name::BrightYellow);
    screen.fill_bg(1, 1, 50, 1, Term::Color::Name::Red);
    screen.print_rect(1, 1, 20, 4);
    screen.print_str(3, 2, "Hola qué tal");

    return screen.render(1, 1, true);
}

int main()
{
    try
    {
        // check if the terminal is capable of handling input
        if(!Term::is_stdin_a_tty())
        {
            std::cout << "The terminal is not attached to a TTY and therefore can't catch user input. Exiting...\n";
            return 1;
        }

        loadSettings();

        Term::Terminal                      terminal{{Term::Options::Option::ClearScreen, Term::Options::Option::Cursor, Term::Options::Option::NoSignalKeys}};
        std::pair<std::size_t, std::size_t> term_size = Term::get_size();
        int                                 pos       = 5;
        int                                 h         = 10;
        std::size_t                         w{10};
        bool                                on = true;

        Utils::Size lastSize{std::get<1>(term_size), std::get<0>(term_size)};
        auto screen{std::make_unique<Term::Window>(lastSize.x(), lastSize.y())};

        Widgets::MainWindow mainWindow;

        mainWindow.onResize(lastSize.x(), lastSize.y());

        while(on)
        {
            screen->clear();

            mainWindow.draw(*screen);

            std::cout << screen->render(1, 1, true) << std::flush;

            auto keyEvent{Term::Platform::read_raw()};

            if(!keyEvent.empty())
            {
                const std::int32_t key{keyEvent.getKey()};
                switch(key)
                {
                case Term::Key::ARROW_LEFT:
                    if(w > 10) w--;
                    break;
                case Term::Key::ARROW_RIGHT:
                    if(w < std::get<1>(term_size) - 5) w++;
                    break;
                case Term::Key::ARROW_UP:
                    if(pos > 1) pos--;
                    break;
                case Term::Key::ARROW_DOWN:
                    if(pos < h) pos++;
                    break;
                case Term::Key::HOME: pos = 1; break;
                case Term::Key::END: pos = h; break;
                case 'q':
                case Term::Key::ESC:
                case Term::Key::CTRL + 'c': on = false; break;
                }
            }

            std::this_thread::sleep_for(100ms);

            auto currentTermSize{Term::get_size()};
            const Utils::Size currentSize{std::get<1>(currentTermSize), std::get<0>(currentTermSize)};

            if(lastSize != currentSize)
            {
                screen = std::make_unique<Term::Window>(currentSize.x(), currentSize.y());
                mainWindow.onResize(currentSize.x(), currentSize.y());
                lastSize = currentSize;
            }
        }
    }
    catch(const Term::Exception& re)
    {
        std::cout << "cpp-terminal error: " << re.what() << std::endl;
        return 2;
    }
    catch(...)
    {
        std::cout << "Unknown error." << std::endl;
        return 1;
    }
    return 0;
}
