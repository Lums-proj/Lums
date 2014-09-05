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

#include <Lums/Angle.h>
#include <cmath>

namespace lm
{
	/**
	 * This class define a tridimensional vector.
	 */
	template <typename T>
	struct Vector3
	{
		/**
		 * Create an empty vector.
		 */
		Vector3() : x(T()), y(T()), z(T()) {}
		
		/**
		 * Create a vector from values.
		 * @param x Value for x
		 * @param y Value for y
		 * @param z Value for z
		 */
		Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
		
		/**
		 * Check if two vectors are equal.
		 * @param rhs The other vector.
		 * @return True if and only if the vector are equal.
		 */
		bool		operator==(const Vector3<T>& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
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
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}
		
		/**
		 * Substract two vectors.
		 * @param rhs The other vector.
		 * @return The current vector.
		 */
		Vector3<T>&	operator-=(const Vector3<T>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		
		/**
		 * Multiply a vector by a coefficient.
		 * @param rhs The coefficient.
		 * @return The current vector.
		 */
		Vector3<T>&	operator*=(const T& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}
		
		/**
		 * Divide a vector by a coefficient.
		 * @param rhs The coefficient.
		 * @return The current vector.
		 */
		Vector3<T>&	operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
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
			return v;
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
			return v;
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
			return v;
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
			return v;
		}
		
		/**
		 * Negate a vector.
		 * @return The opposite of the vector.
		 */
		Vector3<T>	operator-() const
		{
			return Vector3<T>(-x, -y, -z);
		}
        
        /**
		 * Indentity operator.
		 * @return The vector.
		 */
		Vector3<T>	operator+() const
		{
			return *this;
		}

		/**
		 * Set x, y and z.
		 * @param nx The new x value.
		 * @param ny The new y value.
		 * @param nz The new z value.
		 */
		void		Set(const T& nx, const T& ny, const T& nz)
		{
			x = nx;
			y = ny;
			z = nz;
		}
		
		/**
		 * Check if the vector is null.
		 * @return True if the vector is null, false otherwise.
		 */
		bool		Null() const
		{
			return (x == T() && y == T() && z == T());
		}
		
		/**
		 * Get the length of the vector.
		 * This only have a meaning for vectors representing vectors.
		 * @return The length of the vector.
		 */
		double		Length() const
		{
			return std::sqrt(x * x + y * y + z * z);
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
			x /= l;
			y /= l;
			z /= l;
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
			return v;
		}
		
		/**
		 * Get the distance between two vectors.
		 * This only have a meaning for vectors representing points.
		 * @param rhs A vector
		 * @return The distance between the two vectors
		 */
		double		Dist(const Vector3<T>& rhs) const
		{
			return std::sqrt((x - rhs.x) * (x - rhs.x)
							 + (y - rhs.y) * (y - rhs.y)
							 + (z - rhs.z) * (z - rhs.z));
		}
		
		/**
		 * Get the dot product of two vectors.
		 * This only have a meaning for vectors representing vectors.
		 * @param rhs A vector
		 * @return The dot product between the two vectors
		 */
		T			Dot(const Vector3<T>& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
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
			return Vector3<T>(y * rhs.z - z * rhs.y,
							  z * rhs.x - x * rhs.z,
							  x * rhs.y - y * rhs.x);
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

		T			x;
		T			y;
		T			z;
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