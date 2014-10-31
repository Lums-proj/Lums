/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Vector2.h                                    &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VECTOR2_H
#define LUMS_VECTOR2_H

#include <Lums/Angle.h>
#include <cmath>

namespace lm
{
    /**
     * This class define a bidimentional vector.
     */
    template <typename T>
    struct Vector2
    {
        /**
         * Create an empty vector.
         */
        constexpr
        Vector2()
        : x(T()), y(T())
        {
            
        }
        
        /**
         * Create a vector from values.
         * @param x Value for x
         * @param y Value for y
         */
        constexpr
        Vector2(T x, T y)
        : x(x), y(y)
        {
            
        }
        
        /**
         * Check if two vectors are equal.
         * @param rhs The other vector.
         * @return True if and only if the vector are equal.
         */
        constexpr bool
        operator==(const Vector2<T>& rhs) const
        {
            return (x == rhs.x && y == rhs.y);
        }
        
        /**
         * Check if two vectors are not equal.
         * @param rhs The other vector.
         * @return True if and only if the vector are not equal.
         */
        constexpr bool
        operator!=(const Vector2<T>& rhs) const
        {
            return !(*this == rhs);
        }
        
        /**
         * Add two vectors.
         * @param rhs The other vector.
         * @return The current vector.
         */
        Vector2<T>&
        operator+=(const Vector2<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        
        /**
         * Substract two vectors.
         * @param rhs The other vector.
         * @return The current vector.
         */
        Vector2<T>&
        operator-=(const Vector2<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        
        /**
         * Multiply a vector by a coefficient.
         * @param rhs The coefficient.
         * @return The current vector.
         */
        Vector2<T>&
        operator*=(const T& rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }
        
        /**
         * Divide a vector by a coefficient.
         * @param rhs The coefficient.
         * @return The current vector.
         */
        Vector2<T>&
        operator/=(const T& rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }
        
        /**
         * Add two vectors, and return a copy.
         * @param rhs The other vector.
         * @return The sum of the two vectors.
         */
        Vector2<T>
        operator+(const Vector2<T>& rhs) const
        {
            Vector2<T>	v(*this);
            
            v += rhs;
            return v;
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
            return v;
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
            return v;
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
            return v;
        }
        
        /**
         * Negate a vector.
         * @return The opposite of the vector.
         */
        constexpr Vector2<T>
        operator-() const
        {
            return Vector2<T>(-x, -y);
        }
        
        /**
         * Identity operator.
         * @return The vector.
         */
        constexpr Vector2<T>
        operator+() const
        {
            return *this;
        }
        
        /**
         * Set both x and y.
         * @param nx The new x value.
         * @param ny The new y value.
         */
        void
        Set(const T& nx, const T& ny)
        {
            x = nx;
            y = ny;
        }
        
        /**
         * Check if the vector is null.
         * @return True if the vector is null, false otherwise.
         */
        constexpr bool
        Null() const
        {
            return (x == T() && y == T());
        }
        
        /**
         * Get the length of the vector.
         * This only have a meaning for vectors representing vectors.
         * @return The length of the vector.
         */
        constexpr double
        Length() const
        {
            return std::sqrt(x * x + y * y);
        }
        
        /**
         * Normalize the vector.
         * After a call to this function on a non-null vector,
         * it length will become 1.
         * Null vectors are not affected.
         */
        void
        Normalize()
        {
            double	l;
            
            if (Null())
                return;
            l = Length();
            x /= l;
            y /= l;
        }
        
        /**
         * Return a normalized copy of this vector.
         * If this vector is null, this function return a null vector.
         * @return A normalized vector with the same direction as this one.
         */
        Vector2<T>
        Unit() const
        {
            Vector2<T>	v(*this);
            
            v.Normalize();
            return v;
        }
        
        /**
         * Get the distance between two vectors.
         * This only have a meaning for vectors representing points.
         * @param rhs A vector
         * @return The distance between the two vectors
         */
        constexpr double
        Dist(const Vector2<T>& rhs) const
        {
            return std::sqrt((x - rhs.x) * (x - rhs.x)
                             + (y - rhs.y) * (y - rhs.y));
        }
        
        /**
         * Get the dot product of two vectors.
         * This only have a meaning for vectors representing vectors.
         * @param rhs A vector
         * @return The dot product between the two vectors
         */
        constexpr T
        Dot(const Vector2<T>& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        
        /**
         * Get a new vector perpendicular to this one.
         * If this vector is null, a null vector is returned.
         * @return A vector perpendicular to this one.
         */
        constexpr Vector2<T>
        Cross() const
        {
            return Vector2<T>(-y, x);
        }
        
        /**
         * Get the angle between two vector.
         * This only have a meaning for vectors representing vectors.
         * If at least one vector is null, an angle of zero is returned.
         * @param rhs A vector
         * @return The angle between the two vectors
         */
        Angle
        Angle(const Vector2<T>& rhs) const
        {
            double	c;
            
            if (Null() || rhs.Null())
                return (Angle());
            c = Dot(rhs) / (Length() * rhs.Length());
            return Angle::Radians(std::acos(c));
        }
        
        /**
         * The x value
         */
        T	x;
        
        /**
         * The y value
         */
        T	y;
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

#endif