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
#include <iostream>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/Graphics/Image.hpp>

namespace lm
{
	/**
     * @cond
     */
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
				glVertexAttribPointer(Attr, Size, GL_FLOAT, GL_FALSE, TotalSize * sizeof(float), (void*)(SizeCount * sizeof(float)));
				VertexBufferEnable<SizeCount + Size, TotalSize, Tail...>::func();
			}
		};
	}
    /**
     * @endcond
     */
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
		: _vao(0)
		, _vbo(0)
		, _count(0)
		{
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &_vbo);
			glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			internal::VertexBufferEnable<0, size, Attr...>::func();
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
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
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * _count, _values.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
			_values.clear();
		}

		void
		draw(GLenum mode)
		{
			glBindVertexArray(_vao);
			glDrawArrays(mode, 0, _count);
            glBindVertexArray(0);
		}

		void
		reset()
		{
			_values.clear();
			_count = 0;
		}

	private:
		std::vector<float>	_values;
		GLuint				_vao;
		GLuint				_vbo;
		GLuint				_count;
	};

	using VertexBufferP2T2C4 = VertexBuffer<Vertex::Position, 2, Vertex::Texture, 2, Vertex::Color, 4>;
	using VertexBufferP3C4 = VertexBuffer<Vertex::Position, 3, Vertex::Color, 4>;
}

#endif
