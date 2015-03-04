/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    VertexArray.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VERTEX_ARRAY_HPP
#define LUMS_VERTEX_ARRAY_HPP

#include <type_traits>
#include <Lums/GL.hpp>

namespace lm
{
	enum class Vertex
	{
		Color,
		Texture
	};

	namespace internal
	{
		template <Vertex Base, Vertex...>
		struct _VertexOfType
		{
			enum { value = false };
		};

		template <Vertex Base, Vertex Head, Vertex... Queue>
		struct _VertexOfType<Base, Head, Queue...>
		{
			enum { value = (Base == Head) ? true : _VertexOfType<Base, Queue...>::value };
		};

		template <Vertex...>
		struct _VertexLen
		{
			enum { value = 2 };
		};

		template <Vertex Head, Vertex... Queue>
		struct _VertexLen<Head, Queue...>
		{

		};

		template <Vertex... Queue>
		struct _VertexLen<Vertex::Color, Queue...>
		{
			enum { value = 3 + _VertexLen<Queue...>::value };
		};

		template <Vertex... Queue>
		struct _VertexLen<Vertex::Texture, Queue...>
		{
			enum { value = 2 + _VertexLen<Queue...>::value };
		};

		template <size_t N, Vertex Base, Vertex...>
		struct _VertexOffsetHelper
		{
            enum { value = 0 };
		};

		template <size_t N, Vertex Base, Vertex Head, Vertex... Queue>
		struct _VertexOffsetHelper<N, Base, Head, Queue...>
		{
			enum { value = (Base == Head) ? N : _VertexOffsetHelper<N + _VertexLen<Head>::value, Base, Queue...>::value };
		};

		template <Vertex Base, Vertex Head, Vertex... Queue>
		struct _VertexOffset
		{
			enum { value = _VertexOffsetHelper<2, Base, Head, Queue...>::value };
		};

		template <Vertex Head, Vertex... Opt>
		struct _VertexPush
		{
			template <Vertex V = Head, typename... T>
			static typename std::enable_if<V == Vertex::Color>::type
			apply(double* buffer, double r, double g, double b, T... Args)
			{
				buffer[0] = r;
				buffer[1] = g;
				buffer[2] = b;
				forward<sizeof...(Opt)>(buffer + 3, Args...);
			}

			template <Vertex V = Head, typename... T>
			static typename std::enable_if<V == Vertex::Texture>::type
			apply(double* buffer, double x, double y, T... Args)
			{
				buffer[0] = x;
				buffer[1] = y;
				forward<sizeof...(Opt)>(buffer + 2, Args...);
			}

			template <int N, typename... T>
			static typename std::enable_if<N != 0>::type
			forward(double *buffer, T... Args)
			{
				_VertexPush<Opt...>::apply(buffer, Args...);
			}

			template <int N, typename... T>
			static typename std::enable_if<N == 0>::type
			forward(double* buffer)
			{

			}
		};
	}

	template <size_t N, Vertex... Options>
	class VertexArray
	{
	public:
		VertexArray()
		: _count(0)
        , _vertices(0)
		{

		}

		void
		clear()
		{
			_count = 0;
            _vertices = 0;
		}

		template <typename ...T>
		void
		push(double x, double y, T ...Args)
		{
			_buffer[_count] = x;
			_buffer[_count + 1] = y;
			forward<sizeof...(Options)>(_buffer + _count + 2, Args...);
			_count += internal::_VertexLen<Options...>::value;
            _vertices++;
		}

		template <int Len, typename ...T>
		typename std::enable_if<Len != 0>::type
		forward(double* buffer, T... Args)
		{
			internal::_VertexPush<Options...>::apply(buffer, Args...);
		}

		template <int Len, typename ...T>
		typename std::enable_if<Len == 0>::type
		forward(double* buffer)
		{

		}

		void
		draw(GLenum mode) const
		{
			glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_DOUBLE, internal::_VertexLen<Options...>::value * sizeof(double), _buffer);
			enableColor<Options...>();
			enableTexture<Options...>();
            glDrawArrays(mode, 0, _vertices);
			disableTexture<Options...>();
			disableColor<Options...>();
			glDisableClientState(GL_VERTEX_ARRAY);
		}

	protected:
		double 	_buffer[N * internal::_VertexLen<Options...>::value];
		size_t	_count;
        size_t  _vertices;

	private:
		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Color, V...>::value == true>::type
		enableColor() const
		{
			glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(
                3,
                GL_DOUBLE,
                internal::_VertexLen<Options...>::value * sizeof(double),
                _buffer + internal::_VertexOffset<Vertex::Color, Options...>::value
            );
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Color, V...>::value == false>::type
		enableColor() const
		{
		
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Texture, V...>::value == true>::type
		enableTexture() const
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_TEXTURE_2D);
            glTexCoordPointer(
                2,
                GL_DOUBLE,
                internal::_VertexLen<Options...>::value * sizeof(double),
                _buffer + internal::_VertexOffset<Vertex::Texture, Options...>::value
            );
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Texture, V...>::value == false>::type
		enableTexture() const
		{
			glDisable(GL_TEXTURE_2D);
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Color, V...>::value == true>::type
		disableColor() const
		{
			glDisableClientState(GL_COLOR_ARRAY);
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Color, V...>::value == false>::type
		disableColor() const
		{
		
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Texture, V...>::value == true>::type
		disableTexture() const
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		template <Vertex... V>
		typename std::enable_if<internal::_VertexOfType<Vertex::Texture, V...>::value == false>::type
		disableTexture() const
		{
		
		}
	};

	template <size_t N>
	using VertexArrayc = VertexArray<N, Vertex::Color>;
	
	template <size_t N>
	using VertexArrayt = VertexArray<N, Vertex::Texture>;
	
	template <size_t N>
	using VertexArrayct = VertexArray<N, Vertex::Color, Vertex::Texture>;
}

#endif
