/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    Vector2.h                           :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGL_VECTOR2_H
#define NGL_VECTOR2_H

#include <NGL/Angle.h>
#include <cmath>

namespace ngl
{

/**
 * @class Vector2
 * This class define a bidimentional vector.
 */
template <typename T>
class Vector2
{
public:
	/**
	 * Create an empty vector.
	 */
	Vector2() : _x(T()), _y(T()) {}
	
	/**
	 * Create a vector from values.
	 * @param x Value for x
	 * @param y Value for y
	 */
	Vector2(T x, T y) : _x(x), _y(y) {}
	
	/**
	 * Check if two vectors are equal.
	 * @param rhs The other vector.
	 * @return True if and only if the vector are equal.
	 */
	bool		operator==(const Vector2<T>& rhs) const
	{
		return (_x == rhs._x && _y == rhs._y);
	}
	
	/**
	 * Check if two vectors are not equal.
	 * @param rhs The other vector.
	 * @return True if and only if the vector are not equal.
	 */
	bool		operator!=(const Vector2<T>& rhs) const
	{
		return !(*this == rhs);
	}
	
	/**
	 * Add two vectors.
	 * @param rhs The other vector.
	 * @return The current vector.
	 */
	Vector2<T>&	operator+=(const Vector2<T>& rhs)
	{
		_x += rhs._x;
		_y += rhs._y;
		return (*this);
	}
	
	/**
	 * Substract two vectors.
	 * @param rhs The other vector.
	 * @return The current vector.
	 */
	Vector2<T>&	operator-=(const Vector2<T>& rhs)
	{
		_x -= rhs._x;
		_y -= rhs._y;
		return (*this);
	}
	
	/**
	 * Multiply a vector by a coefficient.
	 * @param rhs The coefficient.
	 * @return The current vector.
	 */
	Vector2<T>&	operator-=(const T& rhs)
	{
		_x *= rhs;
		_y *= rhs;
		return (*this);
	}
	
	/**
	 * Divide a vector by a coefficient.
	 * @param rhs The coefficient.
	 * @return The current vector.
	 */
	Vector2<T>&	operator/=(const T& rhs)
	{
		_x /= rhs;
		_y /= rhs;
		return (*this);
	}
	
	/**
	 * Add two vectors, and return a copy.
	 * @param rhs The other vector.
	 * @return The sum of the two vectors.
	 */
	Vector2<T>	operator+(const Vector2<T>& rhs) const
	{
		Vector2<T>	v(*this);

		v += rhs;
		return (v);
	}
	
	/**
	 * Substract two vectors, and return a copy.
	 * @param rhs The other vector.
	 * @return The difference between the two vectors.
	 */
	Vector2<T>	operator-(const Vector2<T>& rhs) const
	{
		Vector2<T>	v(*this);
		
		v -= rhs;
		return (v);
	}
	
	/**
	 * Multiply a vector by a coefficient, and return a copy.
	 * @param rhs A coefficient.
	 * @return The product of the vector and the coefficient.
	 */
	Vector2<T>	operator*(const T& rhs) const
	{
		Vector2<T>	v(*this);
		
		v *= rhs;
		return (v);
	}
	
	/**
	 * Divide a vector by a coefficient, and return a copy.
	 * @param rhs A coefficient.
	 * @return The vector divided by the coefficient.
	 */
	Vector2<T>	operator/(const T& rhs) const
	{
		Vector2<T>	v(*this);
		
		v /= rhs;
		return (v);
	}
	
	/**
	 * Negate a vector.
	 * @return The opposite of the vector.
	 */
	Vector2<T>	operator-() const
	{
		return (Vector2<T>(-_x, -_y));
	}
	
	/**
	 * Get the x value of the vector.
	 * @return The x value of the vector
	 */
	const T&	X() const { return _x; }
	
	/**
	 * Get the y value of the vector.
	 * @return The y value of the vector
	 */
	const T&	Y() const { return _y; }
	
	/**
	 * Set the x value of the vector.
	 * @param x The new x value.
	 */
	void		SetX(const T& x) { _x = x; }
	
	/**
	 * Set the y value of the vector.
	 * @param y The new y value.
	 */
	void		SetY(const T& y) { _y = y; }
	
	/**
	 * Set both x and y.
	 * @param x The new x value.
	 * @param y The new y value.
	 */
	void		Set(const T& x, const T& y) { _x = x; _y = y; }
	
	/**
	 * Check if the vector is null.
	 * @return True if the vector is null, false otherwise.
	 */
	bool		Null() const { return (_x == T() && _y == T()); }
	
	/**
	 * Get the length of the vector.
	 * This only have a meaning for vectors representing points.
	 * @return The length of the vector.
	 */
	double		Length() const { return std::sqrt(_x * _x + _y * _y); }
	
	/**
	 * Normalize the vector.
	 * After a call to this function on a non-null vector,
	 * it length will become 1.
	 * Null vectors are not affected.
	 */
	void		Normalize()
	{
		double	l;

		if (Null())
			return;
		l = Length();
		_x /= l;
		_y /= l;
	}
	
	/**
	 * Get the distance between two vectors.
	 * This only have a meaning for vectors representing points.
	 * @param rhs A vector
	 * @return The distance between the two vectors
	 */
	double		Dist(const Vector2<T>& rhs) const
	{
		return std::sqrt((_x - rhs._x) * (_x - rhs._x)
						 + (_y - rhs._y) * (_y - rhs._y));
	}
	
	/**
	 * Get the dot product of two vectors.
	 * This only have a meaning for vectors representing vectors.
	 * @param rhs A vector
	 * @return The dot product between the two vectors
	 */
	T			Dot(const Vector2<T>& rhs) const
	{
		return _x * rhs._x + _y * rhs._y;
	}
	
	/**
	 * Get the angle between two vector.
	 * This only have a meaning for vectors representing vectors.
	 * If at least one vector is null, an angle of zero is returned.
	 * @param rhs A vector
	 * @return The angle between the two vectors
	 */
	Angle		Angle(const Vector2<T>& rhs) const
	{
		double	c;

		if (Null() || rhs.Null())
			return (Angle());
		c = Dot(rhs) / (Length() * rhs.Length());
		return Angle::Radians(std::acos(c));
	}
	
private:
	T			_x;
	T			_y;
};

/**
 * An alias for Vector2<int>
 */
typedef Vector2<int>	Vector2i;

/**
 * An alias for Vector2<float>
 */
typedef Vector2<float>	Vector2f;

/**
 * An alias for Vector2<double>
 */
typedef Vector2<double>	Vector2d;

/**
 * An alias for Vector2<Angle>
 */
typedef Vector2<Angle>	Vector2a;

}

#endif /* !NGL_VECTOR2_H */