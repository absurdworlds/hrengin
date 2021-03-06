/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Rect_h
#define aw_math_Rect_h
#include <aw/types/types.h>
#include <aw/math/Vector2d.h>
namespace aw {
//! Represents a 2D rectangle, used mostly for GUI rendering
template <class T>
class Rect {
public:
	//! Construct zero-sized rect at (0,0)
	Rect()
		: upperLeft(0,0), lowerRight(0,0)
	{
	}

	//! Construct specifying each coordinate
	Rect(T x, T y, T x2, T y2)
		: upperLeft(x,y), lowerRight(x2,y2)
	{
	}

	//! Construct specifying coordinates as vectors
	Rect(const Vector2d<T>& upperLeft, const Vector2d<T>& lowerRight)
		: upperLeft(upperLeft), lowerRight(lowerRight)
	{
	}


	Rect<T>& operator += (Rect<T> const& other)
	{
		upperLeft  += other.upperLeft;
		lowerRight += other.lowerRight;
		return *this;
	}

	Rect<T> operator + (Rect<T> const& other) const
	{
		Rect<T> tmp = *this;
		tmp.upperLeft  += other.upperLeft;
		tmp.lowerRight += other.lowerRight;
		return tmp;
	}

	Rect<T>& operator -= (Rect<T> const& other)
	{
		upperLeft  -= other.upperLeft;
		lowerRight -= other.lowerRight;
		return *this;
	}

	Rect<T> operator - (Rect<T> const& other) const
	{
		Rect<T> tmp = *this;
		tmp.upperLeft  -= other.upperLeft;
		tmp.lowerRight -= other.lowerRight;
		return tmp;
	}

	Rect<T>& operator += (Vector2d<T> const& vec)
	{
		upperLeft  += vec;
		lowerRight += vec;
		return *this;
	}

	Rect<T>& operator -= (Vector2d<T> const& vec)
	{
		upperLeft  -= vec;
		lowerRight -= vec;
		return *this;
	}

	T getWidth() const
	{
		return lowerRight.x() - upperLeft.x();
	}

	T getHeight() const
	{
		return lowerRight.y() - upperLeft.y();
	}

	Vector2d<T> getUpperLeft() const
	{
		return upperLeft;
	}

	Vector2d<T> getLowerRight() const
	{
		return lowerRight;
	}

	//! Get center of the rectangle.
	Vector2d<T> getCenter() const
	{
		return (lowerRight + upperLeft) / 2;
	}

	void setHeight(T height)
	{
		lowerRight.y() = height + upperLeft.y();
	}

	void setWidth(T width)
	{
		lowerRight.y() = width + upperLeft.x();
	}

	void setPosition(Vector2d<T> position)
	{
		lowerRight += position - upperLeft;
		upperLeft   = position;
	}

	//! Coordinates of upper left corner
	Vector2d<T> upperLeft;
	//! Coordinates of lower right corner
	Vector2d<T> lowerRight;

};

// TODO: rename to contains, and swap arguments
/*!
 * Check if point is inside a rectangle.
 * \param point
 *      Point to test against.
 * \return
 *      true if point is within the rectangle,
 *      false otherwise
 */
template <typename T>
bool pointWithinRect(Vector2d<T> point, Rect<T> rect)
{
	bool isInside = (rect.upperLeft[0] <= point[0]  &&
			 rect.upperLeft[1] <= point[1]  &&
			 point[0] <= rect.lowerRight[0] &&
			 point[1] <= rect.lowerRight[1]);
	return isInside;
}
} // namespace aw
#endif//aw_math_Rect_h
