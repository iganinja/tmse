#include "view.h"
#include "document.h"

namespace TMSE
{

View::View(Document& document) :
    mDocument{&document}
{
}

void View::setViewSize(size_t width, size_t height)
{
    mRenderWindow.width = width;
    mRenderWindow.height = height;
}

void View::moveUp()
{
    if(mCursorPosition.row == 0)
    {
        return;
    }

    -- mCursorPosition.row;

    updateState();
}

void View::moveDown()
{
    if(mCursorPosition.row == mDocument->lineNumber() - 1)
    {
        return;
    }

    ++ mCursorPosition.row;

    updateState();
}

void View::moveLeft()
{
    if(mCursorPosition.column == 0)
    {
        return;
    }

    -- mCursorPosition.column;

    updateState();
}

void View::moveRight()
{
    const auto& line = mDocument->line(mCursorPosition.row);

    if(mCursorPosition.column == line.length())
    {
        return;
    }

    ++ mCursorPosition.column;

    updateState();
}

void View::moveToLineBeginning()
{
    if(mCursorPosition.column == 0)
    {
        return;
    }

    mCursorPosition.column = 0;

    updateState();
}

void View::moveToLineEnding()
{
    const auto& line = mDocument->line(mCursorPosition.row);

    if(mCursorPosition.column == line.length())
    {
        return;
    }

    mCursorPosition.column = line.length();

    updateState();
}

void View::movePageUp()
{

}

void View::movePageDown()
{

}

void View::moveToTop()
{
    if(mCursorPosition.row == 0)
    {
        return;
    }

    mCursorPosition.row = 0;

    updateState();
}

void View::moveToBottom()
{
    if(mCursorPosition.row == mDocument->lineNumber() - 1)
    {
        return;
    }

    mCursorPosition.row = mDocument->lineNumber() - 1;

    updateState();
}

View::DocumentCursorPosition View::documentCursorPosition() const
{
    return mCursorPosition;
}

View::RenderWindow View::renderWindow() const
{
    return mRenderWindow;
}

void View::updateState()
{
    const auto& line = mDocument->line(mCursorPosition.row);

    mCursorPosition.column = std::min(line.length(), mCursorPosition.column);
    mRenderWindow.row = std::min(mCursorPosition.row, mRenderWindow.row);
    mRenderWindow.column = std::min(mCursorPosition.column, mRenderWindow.column);
}

}
