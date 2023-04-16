#pragma once

#include <cpp-terminal/window.hpp>
#include <tasks/task.h>
#include <memory>

#include "utils/size.h"
#include "settings.h"

namespace Widgets
{

class Widget
{
public:
    Widget(/*Widget* parent = nullptr*/);
    virtual ~Widget() = default;

    void draw(Term::Window& window);
    void setPosition(Utils::Position newPosition);
    void setPosition(int newX, int newY);
    void onResize(size_t newWidth, size_t newHeight);
    // Returns true if key has been processsed, false otherwise
    //bool onKey(int32_t key);

    Utils::Position position() const;
    Utils::Size size() const;

    bool isVisible() const;
    void setVisible(bool visible);
    void show();
    void hide();

//    enum class SizeFlags
//    {
//        Fixed,
//        Expanding
//    };

//    using SizeBehavior = Utils::Vector2D<SizeFlags>;

//    SizeBehavior sizeBehavior() const;

//    Widget* parent();
//    void setParent(Widget* parent);

//    std::vector<std::unique_ptr<Widget>>& children();
//    Widget* addChild(std::unique_ptr<Widget>&& child);

//    Olagarro::Tasks::TaskUP tasks();

protected:
    virtual void widgetDraw(Term::Window& window);
    virtual void widgetOnReposition(Utils::Position newPosition);
    virtual void widgetOnResize(size_t newWidth, size_t newHeight);
    //virtual bool widgetOnKey(int32_t key);
    //virtual Olagarro::Tasks::TaskUP widgetTasks();

    enum class HorizontalAnchor
    {
        Left,
        Center,
        Right
    };

    void write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Window& window);
    void write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Color colorBG, Term::Color colorFG, Term::Window& window);
    void write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, const ColorSetting& colors, Term::Window& window);

    void drawRect(int x, int y, size_t width, size_t height, Term::Color colorBG, Term::Color colorFG, Term::Window& window);
    void drawRect(int x, int y, size_t width, size_t height, const ColorSetting& colors, Term::Window& window);

    // A box includes a border
    void drawBox(int x, int y, size_t width, size_t height, Term::Color colorBG, Term::Color colorFG, Term::Window& window);
    void drawBox(int x, int y, size_t width, size_t height, const ColorSetting& colors, Term::Window& window);

    //Widget* mParent{nullptr};
    //std::vector<std::unique_ptr<Widget>> mChildren;
    bool mIsVisible{true};
    Utils::Position mPosition{1, 1};
    Utils::Size mSize;
    //SizeBehavior mSizeBehavior{SizeFlags::Expanding, SizeFlags::Expanding};

private:
    void write(int x, int y, const std::string& text, HorizontalAnchor hAnchor, Term::Color colorBG, Term::Color colorFG, bool useColors, Term::Window& window);
};

using WidgetUP = std::unique_ptr<Widget>;

}
