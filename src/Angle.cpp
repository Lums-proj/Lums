/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Angle.cpp                                    &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <limits>
#include "Angle.h"

using namespace lm;

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

Angle&      Angle::operator+=(const Angle &rhs)
{
    _angle += rhs._angle;
    _angle = Clamp(_angle);
    return *this;
}

Angle&      Angle::operator-=(const Angle &rhs)
{
    _angle -= rhs._angle;
    _angle = Clamp(_angle);
    return *this;
}

Angle&      Angle::operator*=(double rhs)
{
    _angle *= rhs;
    _angle = Clamp(_angle);
    return *this;
}

Angle&      Angle::operator/=(double rhs)
{
    _angle /= rhs;
    _angle = Clamp(_angle);
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

Angle		Angle::operator*(double rhs) const
{
	Angle	a(*this);

	a *= rhs;
	return a;
}

Angle		Angle::operator/(double rhs) const
{
	Angle	a(*this);
	
	a /= rhs;
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
