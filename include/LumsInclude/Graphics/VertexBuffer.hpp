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

    /**
     * @brief Describe a vertex type
     */
	namespace Vertex
	{
		/**
		 * An enum describing a vertex type
		 */
		enum : GLint
		{
			Position = 0,
			Color = 1,
			Texture = 2
		};
	}

	/**
     * @brief A class representing a buffer of vertices
     * @tparam Attr The attributes
     */
	template <GLint... Attr>
	class VertexBuffer
	{
	public:
		static_assert(sizeof...(Attr) % 2 == 0, "Must provide key/value pairs");

		/**
		 * @cond
		 */
		enum { size = internal::VertexBufferSize<Attr...>::size };
		/**
		 * @endcond
		 */

		/**
         * Create a vertex buffer
         */
		VertexBuffer(GLenum hint = GL_STATIC_DRAW)
		: _vao(0)
		, _vbo(0)
		, _count(0)
        , _hint(hint)
		{
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &_vbo);
			glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			internal::VertexBufferEnable<0, size, Attr...>::func();
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/**
         * Push values onto the vertex buffer, according to the attributes
         * @tparam Pack Types for values
         * @param values Values
         */
		template <typename... Pack>
		void
		push(Pack... values)
		{
			internal::VertexBufferPush<size>::push(_values, values...);
			_count++;
		}

		/**
         * Send the vertex buffer into the GPU
         */
		void
		send()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * _count, _values.data(), _hint);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
			_values.clear();
		}

		/**
         * Draw the vertex buffer
         * @param mode The OpenGL draw mode, can be GL_TRIANGLES, GL_LINES or GL_POINTS
         */
		void
		draw(GLenum mode)
		{
			glBindVertexArray(_vao);
			glDrawArrays(mode, 0, _count);
            glBindVertexArray(0);
		}

		/**
         * Reset the vertex buffer
         */
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
        GLenum              _hint;
	};

	/**
     * A vertex buffer with 2 values for position, 2 for texture, and 4 for color
     */
	using VertexBufferP2T2C4 = VertexBuffer<Vertex::Position, 2, Vertex::Texture, 2, Vertex::Color, 4>;

    /**
     * A vertex buffer with 3 values for position, 2 for texture, and 4 for color
     */
    using VertexBufferP3T2C4 = VertexBuffer<Vertex::Position, 3, Vertex::Texture, 2, Vertex::Color, 4>;

	/**
     * A vertex buffer with 3 values for position, and 4 for color
     */
	using VertexBufferP3C4 = VertexBuffer<Vertex::Position, 3, Vertex::Color, 4>;
}

#endif
