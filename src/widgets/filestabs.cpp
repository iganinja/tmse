#include "filestabs.h"
#include "settings.h"

#include <cassert>

namespace Widgets
{

void FilesTabs::addNewUnnamedDocument()
{
    mDocuments.push_back(DocumentInfo{"unnamed " + std::to_string(mDocuments.size())});
}

void FilesTabs::closeDocument(size_t index)
{

}

const std::string& FilesTabs::documentName(size_t index)
{
    return mDocuments.at(index).name;
}

size_t FilesTabs::currentDocumentIndex() const
{
    return mCurrentDocumentIndex;
}

void FilesTabs::setCurrentDocumentIndex(size_t index)
{
    assert(index >= 0 && index < mDocuments.size() && "Provided index is out of bounds");

    mCurrentDocumentIndex = index;
}

void FilesTabs::widgetOnResize(size_t newWidth, size_t newHeight)
{
    mWelcomeBackground.setPosition(0, position().y + 1);
    mWelcomeBackground.onResize(newWidth, newHeight - 1);
}

void FilesTabs::widgetDraw(Term::Window& window)
{
    drawRect(0, 0, size().x, size().y, settings().filesTabsColors, window);

    write(0, 0, " test.txt | jarl.cpp | my_script.sh | another_file.lua", HorizontalAnchor::Left, window);

    mWelcomeBackground.draw(window);
}

}
