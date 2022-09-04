#ifndef VIEW_H
#define VIEW_H

#include <cstddef>

namespace TMSE
{

class Document;

class View
{
public:
    View(Document& document);

    void setViewSize(size_t width, size_t height);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void moveToLineBeginning();
    void moveToLineEnding();

    void movePageUp();
    void movePageDown();

    void moveToTop();
    void moveToBottom();

    struct DocumentCursorPosition
    {
        bool operator == (const DocumentCursorPosition& other) const
        {
            return row == other.row and column == other.column;
        }
        size_t row;
        size_t column;
    };

    DocumentCursorPosition documentCursorPosition() const;

    struct RenderWindow
    {
        bool operator == (const RenderWindow& other) const
        {
            return row == other.row and
                    column == other.column and
                    width == other.width and
                    height == other.height;
        }
        size_t row;
        size_t column;
        size_t width;
        size_t height;
    };

    RenderWindow renderWindow() const;

private:
    void updateState();

    Document* mDocument{nullptr};
    DocumentCursorPosition mCursorPosition{0, 0};
    RenderWindow mRenderWindow{0, 0, 0, 0};
};

}

#endif // VIEW_H
