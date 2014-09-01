/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Angle.h                                      &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_ANGLE_H
#define LUMS_ANGLE_H

#include <cmath>

namespace lm
{
    /**
     * A class used to represent arbitrary angles.
     */
    class Angle
    {
    public:
        /**
         * Create a null angle.
         */
        constexpr Angle() : _angle(0.0) {}
        
        /**
         * Create an angle in turns.
         * This is the same as lm::Angle::Turns
         * @param angle An angle in turns.
         * @return The resulting Angle.
         */
        explicit constexpr Angle(double angle) : _angle(Clamp(angle)) {}

        /**
         * Return true if and only if the two angles are equals.
         * @param rhs The angle to be compared.
         * @return True if the angles are equal, false otherwise.
         */
        bool            operator==(const Angle& rhs) const;

        /**
         * Return false if and only if the two angles are equals.
         * @param rhs The angle to be compared.
         * @return True if the angles are not equal, false otherwise.
         */
        bool            operator!=(const Angle& rhs) const;

        /**
         * Inferior than operator.
         * @param rhs The angle to be compared.
         * @return True if the first angle is inferior to the second one,
         *         false otherwise.
         */
        bool            operator<(const Angle& rhs) const;

        /**
         * Superior than operator.
         * @param rhs The angle to be compared.
         * @return True if the first angle is superior to the second one,
         *         false otherwise.
         */
        bool            operator>(const Angle& rhs) const;

        /**
         * Inferior or equal operator.
         * @param rhs The angle to be compared.
         * @return True if the first angle is inferior or equal to the second
         *         one, false otherwise.
         */
        bool            operator<=(const Angle& rhs) const;

        /**
         * Superior or equal operator.
         * @param rhs The angle to be compared.
         * @return True if the first angle is superior or equal to the second
         *         one, false otherwise.
         */
        bool            operator>=(const Angle& rhs) const;

        /**
         * Return the opposite of an angle.
         * @return The opposite of the angle.
         */
        constexpr Angle operator-() const
        {
            return Angle(1.0 - _angle);
        }
        
        /**
         * Return the same angle.
         * @return The same angle.
         */
        constexpr Angle operator+() const
        {
            return Angle(*this);
        }

        /**
         * Add an angle.
         * @param rhs The angle to be added.
         * @return This angle.
         */
        Angle&          operator+=(const Angle& rhs);

        /**
         * Substract an angle.
         * @param rhs The angle to be substracted.
         * @return This angle.
         */
        Angle&          operator-=(const Angle& rhs);

        /**
         * Multiply an angle with a coefficient.
         * @param rhs A coefficient.
         * @return This angle.
         */
        Angle&          operator*=(double rhs);

        /**
         * Divide an angle with a coefficient.
         * @param rhs A coefficient.
         * @return This angle.
         */
        Angle&          operator/=(double rhs);

        /**
         * Add an angle, and returns a copy of the result.
         * @param rhs The angle to be added.
         * @return A new angle, resulting of the sum.
         */
        Angle           operator+(const Angle& rhs) const;

        /**
         * Substract an angle, and returns a copy of the result.
         * @param rhs The angle to be substracted.
         * @return A new angle, resulting of the difference.
         */
        Angle           operator-(const Angle& rhs) const;

        /**
         * Multiply an angle, and returns a copy of the result.
         * @param rhs A coefficient.
         * @return A new angle, resulting of the product.
         */
        Angle           operator*(double rhs) const;

        /**
         * Divide an angle, and returns a copy of the result.
         * @param rhs A coefficient.
         * @return A new angle, resulting of the division.
         */
        Angle           operator/(double rhs) const;

        /**
         * Create an angle from turns.
         * @param angle Angle in turns
         * @return A new angle with the corresponding value.
         */
        static constexpr  Angle	Turns(double angle)
        {
            return Angle(angle);
        }

        /**
         * Create an angle from radians.
         * @param angle Angle in radians.
         * @return A new angle with the corresponding value.
         */
        static constexpr Angle	Radians(double angle)
        {
            return Angle(angle * (1.0 / (M_PI * 2.0)));
        }

        /**
         * Create an angle from degrees.
         * @param angle Angle in degrees.
         * @return A new angle with the corresponding value.
         */
        static constexpr Angle	Degrees(double angle)
        {
            return Angle(angle * (1.0 / 360.0));
        }

        /**
         * Get the angle value in turns.
         * @return Angle value in turns.
         */
        double			toTurns() const;

        /**
         * Get the angle value in radians.
         * @return Angle value in radians
         */
        double			toRadians() const;

        /**
         * Get the angle value in degrees.
         * @return Angle value in degrees
         */
        double			toDegrees() const;

        /**
         * Get the sinus of the angle.
         * @return the sinus of the angle.
         */
        double          Sin() const;

        /**
         * Get the cosinus of the angle.
         * @return the cosinus of the angle.
         */
        double          Cos() const;

        /**
         * Get the tangent of the angle.
         * @return the tangent of the angle.
         */
        double          Tan() const;

    private:
        constexpr static double Clamp(double a)
        {
            return (a < 0.0 ? 1.0 + (a - static_cast<long long>(a))
                    : (a >= 1.0 ? a - static_cast<long long>(a) : a));
        }
        
        double                  _angle;
    };

    inline namespace literals
    {
        /**
         * User-defined literal for turns.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _turn(long double angle)
        {
            return Angle::Turns(angle);
        }
        
        /**
         * User-defined literal for turns.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _turn(unsigned long long angle)
        {
            return Angle::Turns(angle);
        }

        /**
         * User-defined literal for radians.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _rad(long double angle)
        {
            return Angle::Radians(angle);
        }
        
        /**
         * User-defined literal for radians.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _rad(unsigned long long angle)
        {
            return Angle::Radians(angle);
        }

        /**
         * User-defined literal for degrees.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _deg(long double angle)
        {
            return Angle::Degrees(angle);
        }
        
        /**
         * User-defined literal for degrees.
         * @param angle An angle.
         * @return An Angle object whose value is 'angle'.
         */
        constexpr Angle operator "" _deg(unsigned long long angle)
        {
            return Angle::Degrees(angle);
        }
    }
}

#endif