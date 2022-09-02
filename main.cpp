#include <cpp-terminal/base.hpp>
#include <cpp-terminal/input.hpp>
#include <cpp-terminal/window.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <tasks/taskexecutor.h>

using Term::bg;
using Term::fg;
using Term::Key;
using Term::style;
using Term::Terminal;

std::vector<std::string> loadFile(const std::string& path)
{
    std::ifstream file{path};

    if(not file.is_open())
    {
        return {};
    }

    std::string line;
    std::vector<std::string> lines;

    while(!file.eof())
    {
        std::getline(file, line);

        lines.push_back(line);
    }

    return lines;
}

std::string render(Term::Window_24bit& scr, const std::vector<std::string>& lines) {
    scr.clear();

    const auto lineNumber = std::min(scr.get_h(), lines.size());
    //const auto lineNumber = lines.size();

    for(size_t i = 0; i < lineNumber; ++ i)
    {
        const auto& line = lines[i];
        scr.print_str(1, i + 1, line);
        scr.fill_bg(1, i + 1, line.length(), i + 1, 0, 0, 0);
        scr.fill_fg(1, i + 1, line.length(), i + 1, i + i, i * i, i + i);
    }

    return scr.render(1, 1, true);
}

int main() {
    try {
        // check if the terminal is capable of handling input
        if (!Term::is_stdin_a_tty()) {
            std::cout << "The terminal is not attached to a TTY and therefore "
                         "can't catch user input. Exiting...\n";
            return 1;
        }
        Terminal term(true, true, false, false);
        int rows{}, cols{};
        Term::get_term_size(rows, cols);
        int pos = 5;
        int h = 10;
        int w = 10;
        bool on = true;
        Term::Window_24bit scr(cols, rows);

        const auto lines = loadFile("main.cpp");

        while (on) {
            std::cout << render(scr, lines) << std::flush;
            int key = Term::read_key();
            switch (key) {
                case Key::ARROW_LEFT:
                    if (w > 10)
                        w--;
                    break;
                case Key::ARROW_RIGHT:
                    if (w < cols - 5)
                        w++;
                    break;
                case Key::ARROW_UP:
                    if (pos > 1)
                        pos--;
                    break;
                case Key::ARROW_DOWN:
                    if (pos < h)
                        pos++;
                    break;
                case Key::HOME:
                    pos = 1;
                    break;
                case Key::END:
                    pos = h;
                    break;
                case 'q':
                case Key::ESC:
                    on = false;
                    break;
            }
        }
    } catch (const std::runtime_error& re) {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
        return 1;
    }
    return 0;
}
