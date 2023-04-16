#pragma once

#include <cmath>
#include <algorithm>
#include <ostream>

namespace Utils
{

template<typename T>
struct Vector2D
{
public:
    explicit constexpr Vector2D(T x = 0, T y = 0) : x{x}, y{y}
	{}

	template<typename Type1, typename Type2>
	constexpr Vector2D(Type1 x, Type2 y) :
        x{static_cast<T>(x)},
        y{static_cast<T>(y)}
    {}

    constexpr Vector2D(const Vector2D<T>& other) : x{other.x}, y{other.y} {}

	Vector2D<T>& operator = (const Vector2D<T>& other)
	{
		if(this != &other)
		{
			x = other.x;
			y = other.y;
		}

		return *this;
	}

	float squareModule() const
	{
		return dot(*this);
	}

	float module() const
	{
		return std::sqrt(dot(*this));
	}

	float dot(const Vector2D<T>& other) const
	{
		return x * other.x + y * other.y;
	}

	Vector2D<T>& normalize()
	{
		float m = module();

		if(0 == m)
		{
			return *this;
		}

		x /= m;
		y /= m;

		return *this;
	}

	Vector2D<T> normalized() const
	{
		float m = module();

		if(0 == m)
		{
			return *this;
		}

		return Vector2D<T>(x / m, y / m);
	}

	Vector2D<T>& rotate(float angle)
	{
		const float cosAngle = std::cos(angle);
		const float sinAngle = std::sin(angle);

		const float newX = x * cosAngle - y * sinAngle;
		const float newY = x * sinAngle + y * cosAngle;

		x = newX;
		y = newY;

		return *this;
	}

	Vector2D<T> rotated(float angle) const
	{
		const float cosAngle = std::cos(angle);
		const float sinAngle = std::sin(angle);

		return Vector2D<T>(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle);
	}

	// It assumes this and other vectors are normalized
	float angleAgainst(const Vector2D<T>& other) const
	{
		// Bound dot product to [0..1] range
		const float dotValue = std::max(-1.0f, std::min(1.0f, dot(other)));

		return std::acos(dotValue);
	}

	// It applies normalization to this and other vectors using normalized()
	float angleAgainstN(const Vector2D<T>& other) const
	{
		return normalized().angleAgainst(other.normalized());
	}

	Vector2D<T>& operator += (const Vector2D<T>& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2D<T>& operator -= (const Vector2D<T>& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2D<T>& operator *= (const Vector2D<T>& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vector2D<T>& operator *= (T value)
	{
		x *= value;
		y *= value;

		return *this;
	}

	Vector2D<T>& operator /= (const Vector2D<T>& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vector2D<T>& operator /= (T value)
	{
		x /= value;
		y /= value;

		return *this;
	}

	// 3D cross with 2D vectors (sets Z component to 0). As the two vectors are complanar only new vector's Z component is calculated and returned
	float cross(const Vector2D<T>& other) const
	{
		return (x * other.y) - (y * other.x);
	}

	// Set's a top bound on vector's module if it is bigger than maxModule
	Vector2D<T>& setMaxModule(float maxModule)
    {
        const auto length{module()};

        if(length > maxModule)
		{
            x = (x / length) * maxModule;
            y = (y / length) * maxModule;
		}

		return *this;
	}

	Vector2D<T>& bound(float minModule, float maxModule)
    {
        const auto length{module()};

        if(length < minModule)
        {
            const auto factor{minModule / length};
            x *= factor;
            y *= factor;
		}
        else if(length > maxModule)
        {
            const auto factor{maxModule / length};
            x *= factor;
            y *= factor;
		}

		return *this;
	}

	Vector2D<T> bounded(float minModule, float maxModule) const
    {
        const auto length{module()};

        if(length < minModule)
		{
			return normalized() * minModule;
		}
        else if(length > maxModule)
		{
			return normalized() * maxModule;
		}

		return Vector2D<T>{*this};
	}

	Vector2D<T>& rotate90CW()
	{
		std::swap(x, y);

		x *= -1;

		return *this;
	}

	Vector2D<T> rotated90CW() const
	{
		return Vector2D<T>{-y, x};
	}

	Vector2D<T>& rotate90CCW()
	{
		std::swap(x, y);

		y *= -1;

		return *this;
	}

	Vector2D<T> rotated90CCW() const
	{
		return Vector2D<T>{y, -x};
	}

	bool isNull() const
	{
		return static_cast<T>(0) == x && static_cast<T>(0) == y;
	}

	T x;
	T y;
};

using V2F = Vector2D<float>;
using V2I = Vector2D<int>;
using V2U = Vector2D<unsigned>;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Addition
template<typename T>
Vector2D<T> operator + (const Vector2D<T>& a, const Vector2D<T>& b)
{
	return Vector2D<T>(a.x + b.x, a.y + b.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Substraction
template<typename T>
Vector2D<T> operator - (const Vector2D<T>& a, const Vector2D<T>& b)
{
	return Vector2D<T>(a.x - b.x, a.y - b.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Multiplication
template<typename T>
Vector2D<T> operator * (const Vector2D<T>& a, const Vector2D<T>& b)
{
	return Vector2D<T>(a.x * b.x, a.y * b.y);
}

template<typename T, typename Scalar>
Vector2D<T> operator * (Scalar a, const Vector2D<T>& b)
{
	return Vector2D<T>(a * b.x, a * b.y);
}

template<typename T, typename Scalar>
Vector2D<T> operator * (const Vector2D<T>& a, Scalar b)
{
	return Vector2D<T>(a.x * b, a.y * b);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Division
template<typename T>
Vector2D<T> operator / (const Vector2D<T>& a, const Vector2D<T>& b)
{
	return Vector2D<T>(a.x / b.x, a.y / b.y);
}

template<typename T, typename Scalar>
Vector2D<T> operator / (Scalar a, const Vector2D<T>& b)
{
	return Vector2D<T>(a / b.x, a / b.y);
}

template<typename T, typename Scalar>
Vector2D<T> operator / (const Vector2D<T>& a, Scalar b)
{
	return Vector2D<T>(a.x / b, a.y / b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Other stuff
template<typename T1, typename T2>
bool operator == (const Vector2D<T1>& v1, const Vector2D<T2>& v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

template<typename T1, typename T2>
bool operator != (const Vector2D<T1>& v1, const Vector2D<T2>& v2)
{
    return !(v1 == v2);
}

// Assumes v1 and v2 are normalized
// Returned value is in radians
inline float getAngle(const V2F& v1, const V2F& v2)
{
	return v1.angleAgainst(v2) * (0 < v2.cross(v1)? -1 : 1);
}

inline std::ostream& operator << (std::ostream& stream, const V2F& v)
{
	stream << "Vector2d(" << v.x << ", " << v.y << ")";
	return stream;
}

using Position = Vector2D<int>;

}
