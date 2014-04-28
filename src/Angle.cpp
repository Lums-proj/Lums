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
#include <limits>
#include <Angle.h>

using namespace ngl;

Angle::Angle() : _angle(0.0)
{
	
}

bool		Angle::operator==(const Angle& rhs) const
{
	return (fabs(_angle - rhs._angle) < std::numeric_limits<double>::epsilon());
}

bool		Angle::operator!=(const Angle &rhs) const
{
	return !(*this == rhs);
}

bool		Angle::operator<(const Angle &rhs) const
{
	return (_angle < rhs._angle && *this != rhs);
}


bool		Angle::operator>(const Angle &rhs) const
{
	return !(*this < rhs || *this == rhs);
}

bool		Angle::operator<=(const Angle &rhs) const
{
	return !(*this > rhs);
}

bool		Angle::operator>=(const Angle &rhs) const
{
	return !(*this < rhs);
}

Angle		Angle::operator!() const
{
	Angle	a;

	a._angle = 1.0 - _angle;
	return a;
}

Angle&      Angle::operator+=(const Angle &rhs)
{
    _angle += rhs._angle;
    Clamp();
    return *this;
}

Angle&      Angle::operator-=(const Angle &rhs)
{
    _angle -= rhs._angle;
    Clamp();
    return *this;
}

Angle&      Angle::operator*=(const double rhs)
{
    _angle *= rhs;
    Clamp();
    return *this;
}

Angle&      Angle::operator/=(const double rhs)
{
    _angle /= rhs;
    Clamp();
    return *this;
}

Angle		Angle::operator+(const Angle &rhs) const
{
	Angle	a(*this);

	a += rhs;
	return a;
}

Angle		Angle::operator-(const Angle &rhs) const
{
	Angle	a(*this);
	
	a -= rhs;
	return a;
}

Angle		Angle::operator*(const double rhs) const
{
	Angle	a(*this);
	
	a *= rhs;
	return a;
}

Angle		Angle::operator/(const double rhs) const
{
	Angle	a(*this);
	
	a /= rhs;
	return a;
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

double		Angle::toTurns() const
{
	return _angle;
}

double		Angle::toRadians() const
{
	return _angle * M_PI * 2;
}

double		Angle::toDegrees() const
{
	return _angle * 360.0;
}

double      Angle::Sin() const
{
    return sin(toRadians());
}

double      Angle::Cos() const
{
    return cos(toRadians());
}

double      Angle::Tan() const
{
    return tan(toRadians());
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
