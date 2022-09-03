#include "fileutilities.h"

#include <fstream>
#include <stdexcept>

namespace TMSE
{

Document loadFile(const std::string& fileName)
{
    std::ifstream file{fileName};

    if(not file.is_open())
    {
        throw std::runtime_error{"Can't open " + fileName + " file for reading"};
    }

    std::string line;
    std::vector<std::string> lines;

    while(!file.eof())
    {
        std::getline(file, line);

        if(line.back() == '\n')
        {
            line.pop_back();
        }

        lines.push_back(line);
    }

    return Document{std::move(lines)};
}

void saveFile(const std::string& fileName, const Document& document)
{
    std::ofstream file{fileName};

    if(not file.is_open())
    {
        throw std::runtime_error{"Can't open " + fileName + " file for saving"};
    }

    auto lines{document.lines()};
    std::string fileContent;
    fileContent.reserve(lines.size() * 100); // Some poorly guessed initial value

    for(size_t i = 0; i < lines.size() - 1; ++ i)
    {
        fileContent += lines[i] + "\n";
    }

    fileContent += lines.back();

    file.write(fileContent.data(), fileContent.size());
}

}
