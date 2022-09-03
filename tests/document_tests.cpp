#include "../src/document.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace TMSE;
using namespace std::string_literals;

namespace
{
const std::vector<std::string> TestLines =
{
    "Lorem fistrum torpedor condemor la caidita por la gloria de mi madre pupita.",
    "Jarl se calle ustée pupita de la pradera. Jarl no te digo trigo por no llamarte Rodrigor de la pradera",
    "mamaar no te digo trigo por no llamarte Rodrigor. Te va a hasé pupitaa me cago en tus muelas llevame al sircoo a gramenawer.",
    "Al ataquerl diodenoo te va a hasé pupitaa por la gloria de mi madre fistro",
    "por la gloria de mi madre diodeno",
    "No te digo trigo por no llamarte Rodrigor",
    "amatomaa llevame al sircoo."
};

void checkLineInsertion(size_t row)
{
    Document document;

    document.setLines(TestLines);

    const auto TestLine = "Inserted line"s;

    document.insertLine(row, TestLine);

    EXPECT_EQ(document.lineNumber(), TestLines.size() + 1);

    const auto& documentLines = document.lines();

    for(size_t i = 0; i < row; ++ i)
    {
        EXPECT_EQ(documentLines[i], TestLines[i]);
    }

    for(size_t i = row; i < TestLines.size(); ++ i)
    {
        EXPECT_EQ(documentLines[i + 1], TestLines[i]);
    }
}

void checkLineDeletion(size_t row)
{
    Document document;

    document.setLines(TestLines);

    document.deleteLine(row);

    EXPECT_EQ(document.lineNumber(), TestLines.size() - 1);

    const auto& documentLines = document.lines();

    for(size_t i = 0; i < row; ++ i)
    {
        EXPECT_EQ(documentLines[i], TestLines[i]);
    }

    for(size_t i = row; i < documentLines.size(); ++ i)
    {
        EXPECT_EQ(documentLines[i], TestLines[i + 1]);
    }
}
}

TEST(Document, CreatedDocumentIsEmpty)
{
    const Document document;

    EXPECT_TRUE(document.isEmpty());
    EXPECT_EQ(document.lineNumber(), 0);
    EXPECT_TRUE(document.lines().empty());
}

TEST(Document, ClearMakesDocumentEmpty)
{
    Document document;

    document.setLines(TestLines);

    document.clear();

    EXPECT_TRUE(document.isEmpty());
}


TEST(Document, AddingALineRegistersItOnDocument)
{
    Document document;

    EXPECT_EQ(document.lineNumber(), 0);

    const auto LineText = "Test line"s;

    document.addLine(LineText);

    EXPECT_EQ(document.lineNumber(), 1);
    EXPECT_EQ(document.line(0), LineText);
}

TEST(Document, SetLinesResetsDocument)
{
    Document document;

    const auto TestLine = "Test"s;

    document.addLine(TestLine);

    document.setLines(TestLines);

    EXPECT_EQ(TestLines, document.lines());
}

TEST(Document, AskingForANonExistingLineThrowsException)
{
    const Document document;

    EXPECT_THROW(document.line(10), std::runtime_error);
}

TEST(Document, AskingForAnExistingLineReturnsIt)
{
    Document document;

    document.setLines(TestLines);

    const auto row = rand() % TestLines.size();

    EXPECT_EQ(document.line(row), TestLines[row]);
}

TEST(Document, InsertingALineWorksOK)
{
    for(size_t i = 0; i < TestLines.size(); ++ i)
    {
        checkLineInsertion(i);
    }
}

TEST(Document, DeletingANonExistingLineThrowsAnException)
{
    Document document;

    EXPECT_THROW(document.deleteLine(27), std::runtime_error);
}


TEST(Document, DeletingALineErasesItFromDocument)
{
    for(size_t i = 0; i < TestLines.size(); ++ i)
    {
        checkLineDeletion(i);
    }
}
