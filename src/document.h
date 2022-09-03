#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <string>

namespace TMSE
{
class Document
{
public:
    Document() = default;
    Document(std::vector<std::string>&& lines);

    void clear();
    bool isEmpty() const;

    size_t lineNumber() const;
    const std::vector<std::string>& lines() const;
    const std::string& line(size_t row) const;

    void addLine(const std::string& line);
    void addLine(std::string&& line);

    void insertLine(size_t row, const std::string& line);
    void insertLine(size_t row, std::string&& line);

    void deleteLine(size_t row);

    void setLines(const std::vector<std::string>& lines);
    void setLines(std::vector<std::string>&& lines);

private:
    std::vector<std::string> mLines;
};
}

#endif // DOCUMENT_H
