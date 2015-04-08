/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Vector2.hpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VECTOR2_HPP
#define LUMS_VECTOR2_HPP

#include <cmath>
#include <Lums/Angle.hpp>

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
        : x(T())
        , y(T())
        {
            
        }
        
        /**
         * Create a vector from values.
         * @param x Value for x
         * @param y Value for y
         */
        constexpr
        Vector2(T x, T y)
        : x(x)
        , y(y)
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
        set(const T& nx, const T& ny)
        {
            x = nx;
            y = ny;
        }
        
        /**
         * Check if the vector is null.
         * @return True if the vector is null, false otherwise.
         */
        constexpr bool
        null() const
        {
            return (x == T() && y == T());
        }
        
        /**
         * Get the length of the vector.
         * This only have a meaning for vectors representing vectors.
         * @return The length of the vector.
         */
        constexpr double
        length() const
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
        normalize()
        {
            double	l;
            
            if (null())
                return;
            l = length();
            x /= l;
            y /= l;
        }
        
        /**
         * Return a normalized copy of this vector.
         * If this vector is null, this function return a null vector.
         * @return A normalized vector with the same direction as this one.
         */
        Vector2<T>
        unit() const
        {
            Vector2<T>	v(*this);
            
            v.normalize();
            return v;
        }
        
        /**
         * Get the distance between two vectors.
         * This only have a meaning for vectors representing points.
         * @param rhs A vector
         * @return The distance between the two vectors
         */
        constexpr double
        dist(const Vector2<T>& rhs) const
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
        dot(const Vector2<T>& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }
        
        /**
         * Get a new vector perpendicular to this one.
         * If this vector is null, a null vector is returned.
         * @return A vector perpendicular to this one.
         */
        constexpr Vector2<T>
        cross() const
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
        angle(const Vector2<T>& rhs) const
        {
            double	c;
            
            if (null() || rhs.null())
                return (Angle());
            c = dot(rhs) / (length() * rhs.length());
            return Angle::radians(std::acos(c));
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

    template <>
    struct Vector2<bool>
    {
        constexpr
        Vector2()
        : x(false)
        , y(false)
        {

        }

        constexpr
        Vector2(bool x, bool y)
        : x(x)
        , y(y)
        {

        }

        constexpr
        Vector2(const Vector2<bool>& rhs)
        : x(rhs.x)
        , y(rhs.y)
        {

        }

        bool    x:1;
        bool    y:1;
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

    /**
     * An anias for Vector2<bool>
     */
    typedef Vector2<bool>   Vector2b;
}

#endif