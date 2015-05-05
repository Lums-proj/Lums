/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    VertexBuffer.hpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VERTEX_BUFFER_HPP
#define LUMS_VERTEX_BUFFER_HPP

#include <type_traits>
#include <vector>
#include <Lums/GL.hpp>
#include <Lums/Image.hpp>

namespace lm
{
	namespace internal
	{
		template <GLint Size>
		struct VertexBufferPush
		{
			template <float, float... Pack>
			static void
			push(std::vector<float>& vect, float v, Pack... values)
			{
				vect.push_back(v);
				VertexBufferPush<Size - 1>::push(vect, values...);
			}
		};

		template <>
		struct VertexBufferPush<0>
		{
			static void
			push(std::vector<float>& vect)
			{

			}
		};

		template <GLint... Tail>
		struct VertexBufferSize
		{
			enum { size = 0 };
		};

		template <GLint Attr, GLint Size, GLint... Tail>
		struct VertexBufferSize<Attr, Size, Tail...>
		{
			enum { size = Size + VertexBufferSize<Tail...>::size };
		};
	}

	namespace Vertex
	{
		enum : GLint
		{
			Position = 0,
			Color = 1,
			Texture = 2
		};
	}

	template <GLint... Attr>
	class VertexBuffer
	{
	public:
		static_assert(sizeof...(Attr) % 2 == 0, "Must provide key/value pairs");

		enum { size = internal::VertexBufferSize<Attr...>::size };

		template <float... Pack>
		void
		push(Pack... values)
		{
			internal::VertexBufferPush<size>::push(_values, values...);
		}

	private:
		std::vector<float>	_values;
	};

	using VertexBuffer2v = VertexBuffer<Vertex::Position, 2>;
}

#endif
