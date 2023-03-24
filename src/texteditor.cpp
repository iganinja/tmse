#include "texteditor.h"

#include <tasks/serial.h>
#include <tasks/wait.h>
#include <tasks/execute.h>
#include <tasks/repeat.h>

#include <cpp-terminal/color.hpp>

#include <chrono>
#include <thread>

#include <iostream>

using namespace Olagarro::Tasks;
using namespace std::chrono;
using namespace std::chrono_literals;
using Term::Key;
using Term::style;
using Term::Terminal;
using Term::Color;

namespace TMSE
{

TextEditor::TextEditor() :
    mView{mDocument}
{
    const auto size{Term::get_size()};

    std::cout << "Terminal size: " << color_fg(Term::Color::Name::BrightRed) << size.second << "x" << color_fg(Color::Name::Red) << size.first << "\n";

    mTerminalWindow = std::make_unique<Term::Window>(size.first, size.second);

    createTasks();
}

bool TextEditor::run()
{
    std::cout << "Editor started!\n";

    const auto totalStart = high_resolution_clock::now();

    float deltaTime = 0.0f;

    while(mKeepRunning)
    {
        const auto start = high_resolution_clock::now();

        mExecutor.update(deltaTime);

        std::this_thread::sleep_for(20ms);

        const auto stop = high_resolution_clock::now();
        const auto duration = duration_cast<milliseconds>(stop - start);
        deltaTime = duration.count() / 1000.0f;
    }

    std::cout << "Total time = " << duration_cast<milliseconds>(high_resolution_clock::now() - totalStart).count() << "ms\n";

    return 0;
}

void TextEditor::createTasks()
{
    mExecutor.addTask(
                        repeatForever(
                            serial(
                                wait(1.0f),
                                execute([this]()
                                {
                                    //mKeepRunning = false;
                                    const auto size{Term::get_size()};

                                    std::cout << "Terminal size: " << color_fg(Term::Color::Name::BrightRed) << size.second << "x" << color_fg(Color::Name::Red) << size.first << "\n";
                                })
                            )
                        )
                      );
}

}