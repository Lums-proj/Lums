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

private:
	void			Clamp();
	double			_angle;
};
	
}

#endif /* !NGL_ANGLE_H */