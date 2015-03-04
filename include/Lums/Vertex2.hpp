/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Vertex2.hpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VERTEX2_HPP
#define LUMS_VERTEX2_HPP

#include <Lums/Vertex.hpp>
#include <Lums/Vector2.hpp>
#include <Lums/GL.hpp>

namespace lm
{

	template <lm::Vertex>
	struct _Vertex2Option
	{
		
	};

	template <>
	struct _Vertex2Option <lm::Vertex::Color>
	{
		struct
		{
			GLdouble	r;
			GLdouble	g;
			GLdouble	b;
		} color;
	};

	template <>
	struct _Vertex2Option <lm::Vertex::Texture>
	{
		lm::Vector2d	texture;
	};

	template <>
	struct _Vertex2Option <lm::Vertex::Normal>
	{
		lm::Vector2d	normal;
	};

	template <lm::Vertex...>
	struct _Vertex2Compose
	{

	};

	template <lm::Vertex Opt, lm::Vertex... Options>
	struct _Vertex2Compose<Opt, Options...> : _Vertex2Option<Opt>, _Vertex2Compose<Options...>
	{

	};

	template <lm::Vertex ...Options>
	struct Vertex2 : _Vertex2Compose<Options...>
	{
		lm::Vector2d	pos;
	};

	typedef Vertex2<Vertex::Texture>	Vertex2t;
}

#endif