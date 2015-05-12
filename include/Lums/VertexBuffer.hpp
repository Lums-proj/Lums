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
#include <Lums/OpenGL.hpp>
#include <Lums/Image.hpp>

namespace lm
{
	namespace internal
	{
		template <GLint Size>
		struct VertexBufferPush
		{
			template <typename... Pack>
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

		template <GLint...>
		struct VertexBufferSize
		{
			enum { size = 0 };
		};

		template <GLint Attr, GLint Size, GLint... Tail>
		struct VertexBufferSize <Attr, Size, Tail...>
		{
			enum { size = Size + VertexBufferSize<Tail...>::size };
		};

		template <GLint, GLint, GLint...>
		struct VertexBufferEnable
		{
			static void func() {};
		};

		template <GLint SizeCount, GLint TotalSize, GLint Attr, GLint Size, GLint... Tail>
		struct VertexBufferEnable <SizeCount, TotalSize, Attr, Size, Tail...>
		{
			static void
			func()
			{
				glEnableVertexAttribArray(Attr);
				glVertexAttribPointer(Attr, Size, GL_FLOAT, GL_FALSE, TotalSize, (void*)(SizeCount * sizeof(float)));
				VertexBufferEnable<SizeCount + Size, TotalSize, Tail...>::func();
			}
		};

		template <GLint...>
		struct VertexBufferDisable
		{
			static void func() {};
		};

		template <GLint Attr, GLint Size, GLint... Tail>
		struct VertexBufferDisable <Attr, Size, Tail...>
		{
			static void
			func()
			{
				glDisableVertexAttribArray(Attr);
				VertexBufferDisable<Tail...>::func();
			}
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

		VertexBuffer()
		: _vbo(0)
		, _count(0)
		{
			glGenBuffers(1, &_vbo);
		}

		template <typename... Pack>
		void
		push(Pack... values)
		{
			internal::VertexBufferPush<size>::push(_values, values...);
			_count++;
		}

		void
		send()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), _values.data(), GL_DYNAMIC_DRAW);
			_values.clear();
		}

		void
		draw(GLenum mode)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			internal::VertexBufferEnable<0, size, Attr...>::func();
			glDrawArrays(mode, 0, _count);
			internal::VertexBufferDisable<Attr...>::func();
		}

		void
		reset()
		{
			_values.clear();
			_count = 0;
		}

	private:
		std::vector<float>	_values;
		GLuint				_vbo;
		GLuint				_count;
	};

	using VertexBufferP2T2C4 = VertexBuffer<Vertex::Position, 2, Vertex::Texture, 2, Vertex::Color, 4>;
}

#endif
