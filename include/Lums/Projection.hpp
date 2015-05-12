/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Projection.hpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_PROJECTION_HPP
#define LUMS_PROJECTION_HPP

#include <Lums/Matrix.hpp>

namespace lm
{
	struct Projection
	{
		Projection()
		{
			model = view = projection = Matrix4f::identity();
		}

		Matrix4f model;
		Matrix4f view;
		Matrix4f projection;
	};
}

#endif
