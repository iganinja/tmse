#include "fileutilities.h"

#include <fstream>
#include "utils/exception.h"

namespace TMSE
{

Document loadFile(const std::string& fileName)
{
    std::ifstream file{fileName};

    if(!file.is_open())
    {
        THROW(Utils::CantOpenFile{fileName})
    }

    std::string line;
    std::vector<std::string> lines;

    while(!file.eof())
    {
        std::getline(file, line);
        lines.push_back(line);
    }

    for(size_t i = 0; i < lines.size() - 1; ++ i)
    {
        auto& line = lines[i];

        if(line.back() == '\n')
        {
            line.pop_back();
        }
    }

    Document document{std::move(lines)};

    if(lines.back().back() == '\n')
    {
        document.addLine("");
    }

    return document;
}

void saveFile(const std::string& fileName, const Document& document)
{
    std::ofstream file{fileName};

    if(!file.is_open())
    {
        THROW(Utils::CantOpenFile{fileName})
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
