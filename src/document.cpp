#include "document.h"

#include <stdexcept>

namespace TMSE
{

Document::Document(const std::vector<std::string>& lines) :
    mLines{lines}
{

}

void Document::clear()
{
    mLines.clear();
}

bool Document::isEmpty() const
{
    return lines().empty();
}

size_t Document::lineNumber() const
{
    return lines().size();
}

const std::vector<std::string>& Document::lines() const
{
    return mLines;
}

const std::string& Document::line(size_t row) const
{
    if(row >= lineNumber())
    {
        throw std::runtime_error{"Provided row (" + std::to_string(row) + " is out of boundaries"};
    }

    return mLines[row];
}

void Document::addLine(const std::string& line)
{
    mLines.push_back(line);
}

void Document::addLine(std::string&& line)
{
    mLines.push_back(std::move(line));
}

void Document::insertLine(size_t row, const std::string& line)
{
    mLines.insert(mLines.begin() + row, line);
}

void Document::insertLine(size_t row, std::string&& line)
{
    mLines.insert(mLines.begin() + row, std::move(line));
}

void Document::deleteLine(size_t row)
{
    if(row >= lineNumber())
    {
        throw std::runtime_error{"Provided row (" + std::to_string(row) + " is out of boundaries"};
    }

    mLines.erase(mLines.begin() + row);
}

void Document::setLines(const std::vector<std::string>& lines)
{
    mLines = lines;
}

void Document::setLines(std::vector<std::string>&& lines)
{
    mLines = lines;
}

}
