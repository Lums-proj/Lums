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
     * @param The angle to be compared
     * Return true if and only if the two angles are equals.
     */
    bool            operator==(const Angle& rhs);
    
    /**
     * @param The angle to be compared
     * Return false if and only if the two angles are equals.
     */
    bool            operator!=(const Angle& rhs);
    
    /**
     * @param The angle to be compared
     * Inferior than operator.
     */
    bool            operator<(const Angle& rhs);
    
    /**
     * @param The angle to be compared
     * Superior than operator.
     */
    bool            operator>(const Angle& rhs);
    
    /**
     * @param The angle to be compared
     * Inferior or equal operator.
     */
    bool            operator<=(const Angle& rhs);
    
    /**
     * @param The angle to be compared
     * Superior or equal operator.
     */
    bool            operator>=(const Angle& rhs);
    
    /**
     * Return the opposite of an angle.
     */
    Angle           operator!();
    
    /**
     * @param The angle to be added
     * Add an angle.
     */
	Angle&          operator+=(const Angle& rhs);
    
    /**
     * @param The angle to be substracted
     * Substract an angle.
     */
	Angle&          operator-=(const Angle& rhs);
    
    /**
     * @param A coefficient
     * Multiply an angle with a coefficient.
     */
	Angle&          operator*=(const double rhs);
    
    /**
     * @param A coefficient
     * Divide an angle with a coefficient.
     */
	Angle&          operator/=(const double rhs);
    
    /**
     * @param The angle to be added
     * Add an angle, and returns a copy of the result.
     */
    Angle           operator+(const Angle& rhs);
    
    /**
     * @param The angle to be substracted
     * Substract an angle, and returns a copy of the result.
     */
    Angle           operator-(const Angle& rhs);
    
    /**
     * @param A coefficient
     * Multiply an angle, and returns a copy of the result.
     */
    Angle           operator*(const double rhs);
    
    /**
     * @param A coefficient
     * Divide an angle, and returns a copy of the result.
     */
    Angle           operator/(const double rhs);
    
    /**
	 * @param angle in turns
	 * Create an angle from turns.
	 */
	static Angle	Turns(double angle);
	
	/**
	 * @param angle in radians
	 * Create an angle from radians.
	 */
	static Angle	Radians(double angle);
	
	/**
	 * @param angle in degrees
	 * Create an angle from degrees.
	 */
	static Angle	Degrees(double angle);
	
	/**
	 * @return Angle value in turns
	 * Get the angle value in turns.
	 */
	double			toTurns();
	
	/**
	 * @return Angle value in radians
	 * Get the angle value in radians.
	 */
	double			toRadians();
	
	/**
	 * @return Angle value in degrees
	 * Get the angle value in degrees.
	 */
	double			toDegrees();
    
    /**
     * @return the sinus of the angle.
     * Get the sinus of the angle.
     */
    double          Sin();
    
    /**
     * @return the cosinus of the angle.
     * Get the cosinus of the angle.
     */
    double          Cos();
    
    /**
     * @return the tangent of the angle.
     * Get the tangent of the angle.
     */
    double          Tan();

private:
	void			Clamp();
	double			_angle;
};
	
}

#endif /* !NGL_ANGLE_H */