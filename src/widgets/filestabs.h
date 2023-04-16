#pragma once

#include "widget.h"
#include "widgets/welcomebackground.h"

#include <vector>


namespace Widgets
{

class FilesTabs : public Widget
{
public:
    void addNewUnnamedDocument();
    void closeDocument(size_t index);
    const std::string& documentName(size_t index);
    size_t currentDocumentIndex() const;
    void setCurrentDocumentIndex(size_t index);

private:
    void widgetOnResize(size_t newWidth, size_t newHeight) override;
    void widgetDraw(Term::Window& window) override;

    Widgets::WelcomeBackground mWelcomeBackground;

    struct DocumentInfo
    {
        std::string name;
    };

    std::vector<DocumentInfo> mDocuments;
    size_t mCurrentDocumentIndex{0};
};

}
