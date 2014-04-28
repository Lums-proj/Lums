/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    NGL_Test.cpp                        :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#include <NGL/NGL.h>
#include "NGL_Test.h"

#include <cassert>
#include <cmath>

#define FLO_EQ(a, b)		(((a)-(b)) < 0.001 && ((a)-(b)) > -0.001)

using namespace		std;
using namespace		ngl;

void		test_angle()
{
	Angle	a;
	Angle	b = Angle::Turns(2);
	Angle	c = Angle::Turns(0.2);
	Angle	d = Angle::Turns(2.4);
	Angle	e = Angle::Turns(-0.6);
	Angle	f = Angle::Radians(M_PI / 2.0);

	assert(FLO_EQ(a.toTurns(), 0.0));
	assert(FLO_EQ(b.toTurns(), 0.0));
	assert(FLO_EQ(c.toTurns(), 0.2));
	assert(FLO_EQ(d.toTurns(), 0.4));
	assert(FLO_EQ(e.toTurns(), 0.4));
	assert(FLO_EQ(f.toDegrees(), 90.0));
}

int			main()
{
	NGL_Test("Angle", test_angle);
	NGL_Test::Run();
}