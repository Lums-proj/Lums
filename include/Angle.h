/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    Angle.h                             :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGL_ANGLE_H
#define NGL_ANGLE_H

namespace ngl
{
/**
 * @class Angle
 * A class used to represent arbitrary angles.
 */
class Angle
{
public:
	/**
	 * Create a null angle.
	 */
	Angle();
    
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
     * @return True if the first angle is inferior or equal to the second one,
     *         false otherwise.
     */
    bool            operator<=(const Angle& rhs) const;
    
    /**
     * Superior or equal operator.
     * @param rhs The angle to be compared.
     * @return True if the first angle is superior or equal to the second one,
     *         false otherwise.
     */
    bool            operator>=(const Angle& rhs) const;
    
    /**
     * Return the opposite of an angle.
     * @return The opposite of the angle.
     */
    Angle           operator-() const;
    
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
	static Angle	Turns(double angle);
	
	/**
	 * Create an angle from radians.
     * @param angle Angle in radians.
     * @return A new angle with the corresponding value.
	 */
	static Angle	Radians(double angle);
	
	/**
	 * Create an angle from degrees.
     * @param angle Angle in degrees.
     * @return A new angle with the corresponding value.
	 */
	static Angle	Degrees(double angle);
	
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
	void			Clamp();
	double			_angle;
};
	
}

#endif /* !NGL_ANGLE_H */