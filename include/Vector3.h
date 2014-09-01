/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Vector3.h                                    &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VECTOR3_H
#define LUMS_VECTOR3_H

#include <NGL/Angle.h>
#include <cmath>

namespace lm
{
	/**
	 * This class define a tridimensional vector.
	 */
	template <typename T>
	class Vector3
	{
	public:
		/**
		 * Create an empty vector.
		 */
		Vector3() : _x(T()), _y(T()), _z(T()) {}
		
		/**
		 * Create a vector from values.
		 * @param x Value for x
		 * @param y Value for y
		 * @param z Value for z
		 */
		Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}
		
		/**
		 * Check if two vectors are equal.
		 * @param rhs The other vector.
		 * @return True if and only if the vector are equal.
		 */
		bool		operator==(const Vector3<T>& rhs) const
		{
			return (_x == rhs._x && _y == rhs._y && _z == rhs._z);
		}
		
		/**
		 * Check if two vectors are not equal.
		 * @param rhs The other vector.
		 * @return True if and only if the vector are not equal.
		 */
		bool		operator!=(const Vector3<T>& rhs) const
		{
			return !(*this == rhs);
		}
		
		/**
		 * Add two vectors.
		 * @param rhs The other vector.
		 * @return The current vector.
		 */
		Vector3<T>&	operator+=(const Vector3<T>& rhs)
		{
			_x += rhs._x;
			_y += rhs._y;
			_z += rhs._z;
			return (*this);
		}
		
		/**
		 * Substract two vectors.
		 * @param rhs The other vector.
		 * @return The current vector.
		 */
		Vector3<T>&	operator-=(const Vector3<T>& rhs)
		{
			_x -= rhs._x;
			_y -= rhs._y;
			_z -= rhs._z;
			return (*this);
		}
		
		/**
		 * Multiply a vector by a coefficient.
		 * @param rhs The coefficient.
		 * @return The current vector.
		 */
		Vector3<T>&	operator*=(const T& rhs)
		{
			_x *= rhs;
			_y *= rhs;
			_z *= rhs;
			return (*this);
		}
		
		/**
		 * Divide a vector by a coefficient.
		 * @param rhs The coefficient.
		 * @return The current vector.
		 */
		Vector3<T>&	operator/=(const T& rhs)
		{
			_x /= rhs;
			_y /= rhs;
			_z /= rhs;
			return (*this);
		}
		
		/**
		 * Add two vectors, and return a copy.
		 * @param rhs The other vector.
		 * @return The sum of the two vectors.
		 */
		Vector3<T>	operator+(const Vector3<T>& rhs) const
		{
			Vector3<T>	v(*this);
			
			v += rhs;
			return (v);
		}
		
		/**
		 * Substract two vectors, and return a copy.
		 * @param rhs The other vector.
		 * @return The difference between the two vectors.
		 */
		Vector3<T>	operator-(const Vector3<T>& rhs) const
		{
			Vector3<T>	v(*this);
			
			v -= rhs;
			return (v);
		}
		
		/**
		 * Multiply a vector by a coefficient, and return a copy.
		 * @param rhs A coefficient.
		 * @return The product of the vector and the coefficient.
		 */
		Vector3<T>	operator*(const T& rhs) const
		{
			Vector3<T>	v(*this);
			
			v *= rhs;
			return (v);
		}
		
		/**
		 * Divide a vector by a coefficient, and return a copy.
		 * @param rhs A coefficient.
		 * @return The vector divided by the coefficient.
		 */
		Vector3<T>	operator/(const T& rhs) const
		{
			Vector3<T>	v(*this);
			
			v /= rhs;
			return (v);
		}
		
		/**
		 * Negate a vector.
		 * @return The opposite of the vector.
		 */
		Vector3<T>	operator-() const
		{
			return (Vector3<T>(-_x, -_y, -_z));
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
		 * Get the z value of the vector.
		 * @return The z value of the vector
		 */
		const T&	Z() const { return _z; }
		
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
		 * Set the z value of the vector.
		 * @param z The new z value.
		 */
		void		SetZ(const T& z) { _z = z; }
		
		/**
		 * Set x, y and z.
		 * @param x The new x value.
		 * @param y The new y value.
		 * @param z The new z value.
		 */
		void		Set(const T& x, const T& y, const T& z)
		{
			_x = x;
			_y = y;
			_z = z;
		}
		
		/**
		 * Check if the vector is null.
		 * @return True if the vector is null, false otherwise.
		 */
		bool		Null() const
		{
			return (_x == T() && _y == T() && _z == T());
		}
		
		/**
		 * Get the length of the vector.
		 * This only have a meaning for vectors representing vectors.
		 * @return The length of the vector.
		 */
		double		Length() const
		{
			return std::sqrt(_x * _x + _y * _y + _z * _z);
		}
		
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
			_z /= l;
		}
		
		/**
		 * Return a normalized copy of this vector.
		 * If this vector is null, this function return a null vector.
		 * @return A normalized vector with the same direction as this one.
		 */
		Vector3<T>	Unit() const
		{
			Vector3<T>	v(*this);
			
			v.Normalize();
			return (v);
		}
		
		/**
		 * Get the distance between two vectors.
		 * This only have a meaning for vectors representing points.
		 * @param rhs A vector
		 * @return The distance between the two vectors
		 */
		double		Dist(const Vector3<T>& rhs) const
		{
			return std::sqrt((_x - rhs._x) * (_x - rhs._x)
							 + (_y - rhs._y) * (_y - rhs._y)
							 + (_z - rhs._z) * (_z - rhs._z));
		}
		
		/**
		 * Get the dot product of two vectors.
		 * This only have a meaning for vectors representing vectors.
		 * @param rhs A vector
		 * @return The dot product between the two vectors
		 */
		T			Dot(const Vector3<T>& rhs) const
		{
			return _x * rhs._x + _y * rhs._y + _z * rhs._z;
		}
		
		/**
		 * Get a new vector perpendicular to a pair of vectors.
		 * If one vector is null, a null vector is returned.
		 * @param rhs A vector.
		 * @return A vector perpendicular to both vectors.
		 */
		Vector3<T>	Cross(const Vector3<T>& rhs) const
		{
			if (Null() || rhs.Null())
				return Vector3<T>();
			return Vector3<T>(_y * rhs._z - _z * rhs._y,
							  _z * rhs._x - _x * rhs._z,
							  _x * rhs._y - _y * rhs._x);
		}
		
		/**
		 * Get the angle between two vector.
		 * This only have a meaning for vectors representing vectors.
		 * If at least one vector is null, an angle of zero is returned.
		 * @param rhs A vector
		 * @return The angle between the two vectors
		 */
		Angle		Angle(const Vector3<T>& rhs) const
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
		T			_z;
	};
	
	/**
	 * An alias for Vector3<int>
	 */
	typedef Vector3<int>	Vector3i;
	
	/**
	 * An alias for Vector3<float>
	 */
	typedef Vector3<float>	Vector3f;
	
	/**
	 * An alias for Vector3<double>
	 */
	typedef Vector3<double>	Vector3d;
	
	/**
	 * An alias for Vector3<Angle>
	 */
	typedef Vector3<Angle>	Vector3a;
}

#endif