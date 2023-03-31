#pragma once

namespace Utils
{

template<typename T>
class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(T x, T y) :
        mX{x}, mY{y}
    {
    }
    void setX(T newX)
    {
        mX = newX;
    }
    void setY(T newY)
    {
        mY = newY;
    }
    T x() const
    {
        return mX;
    }
    T y() const
    {
        return mY;
    }
    bool operator == (const Vector2D<T> other) const
    {
        return x() == other.x() and y() == other.y();
    }
    bool operator != (const Vector2D<T> other) const
    {
        return x() != other.x() or y() != other.y();
    }

private:
    T mX{};
    T mY{};
};

using Position = Vector2D<int>;

}
