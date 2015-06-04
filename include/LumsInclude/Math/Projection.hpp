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

#include <LumsInclude/Math/Matrix.hpp>

namespace lm
{
	/**
	 * @brief An helper struct used to define a projection
	 */
	struct Projection
	{
		/**
    	 * Create the identity projection
     	 */
		Projection()
		{
			model = view = projection = Matrix4f::identity();
		}

		/**
    	 * The model
     	 */
		Matrix4f model;

		/**
    	 * The view
     	 */
		Matrix4f view;

		/**
    	 * The projection
     	 */
		Matrix4f projection;
	};
}

#endif
