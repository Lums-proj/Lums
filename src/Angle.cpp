/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    Angle.cpp                           :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <Angle.h>

using namespace ngl;

Angle::Angle() : _angle(0.0)
{
	
}

Angle		Angle::Turns(double angle)
{
	Angle	a;

	a._angle = angle;
	a.Clamp();
	return a;
}

Angle		Angle::Radians(double angle)
{
	Angle	a;
	
	a._angle = angle * (1.0 / (M_PI * 2) );
	a.Clamp();
	return a;
}

Angle		Angle::Degrees(double angle)
{
	Angle	a;
	
	a._angle = angle * (1.0 / 360.0);
	a.Clamp();
	return a;
}

double		Angle::toTurns()
{
	return _angle;
}

double		Angle::toRadians()
{
	return _angle * M_PI * 2;
}

double		Angle::toDegrees()
{
	return _angle * 360.0;
}

void		Angle::Clamp()
{
	if (_angle < 0.0)
	{
		_angle = 1.0 + (_angle - static_cast<int>(_angle));
	}
	if (_angle >= 1.0)
	{
		_angle = (_angle - static_cast<int>(_angle));
	}
}
