/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Batch2.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BATCH2_HPP
#define LUMS_BATCH2_HPP

#include <vector>
#include <cstdlib>
#include <type_traits>
#include <Lums/Vertex2.hpp>
#include <Lums/GL.hpp>

#define BATCH_SIZE	0x100

namespace lm
{
	template <typename T, GLenum Poly>
	class Batch2
	{
	public:
		Batch2()
		: _buffer(new T[BATCH_SIZE])
		, _count(0)
		, _alloc(BATCH_SIZE)
		{

		}

		Batch2(const Batch2<T, Poly>& rhs)
		: _buffer(new T[rhs._alloc])
		, _count(rhs._count)
		, _alloc(rhs._alloc)
		{
			memcpy(_buffer, rhs._buffer, _alloc * sizeof(T));
		}

		Batch2(Batch2<T, Poly>&& rhs)
		: _buffer(rhs._buffer)
		, _count(rhs._count)
		, _alloc(rhs._alloc)
		{
			rhs._buffer = nullptr;
		}

		Batch2<T, Poly>&
		operator=(const Batch2<T, Poly>& rhs)
		{
			delete [] _buffer;
			_alloc = rhs._alloc;
			_count = rhs._count;
			_buffer = new T[_alloc];
			memcpy(_buffer, rhs._buffer, _alloc * sizeof(T));
			return *this;
		}

		Batch2<T, Poly>&
		operator=(Batch2<T, Poly>&& rhs)
		{
			delete [] _buffer;
			_alloc = rhs._alloc;
			_count = rhs._count;
			_buffer = rhs._buffer;
			rhs._buffer = nullptr;
			return *this;
		}

		void
		clear()
		{
			_count = 0;
		}

		void
		draw() const
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			enableState<Vertex::Texture>(GL_TEXTURE_COORD_ARRAY);
			enableState<Vertex::Color>(GL_COLOR_ARRAY);
			
			disableState<Vertex::Color>(GL_COLOR_ARRAY);
			disableState<Vertex::Texture>(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		void
		addVertex(const T& vertex)
		{
			if (_count == _alloc)
			{
				T* nBuffer = new T[_alloc + BATCH_SIZE];
				memcpy(nBuffer, _buffer, _alloc * sizeof(T));
				delete [] _buffer;
				_buffer = nBuffer;
			}
			_buffer[_count++] = vertex;
		}

		~Batch2()
		{
			delete [] _buffer;
		}

	private:

		template <Vertex V>
		typename std::enable_if<std::is_base_of<_Vertex2Option<V>, T>::value>::type
		enableState(GLenum state) const
		{
			glEnableClientState(state);
		}

		template <Vertex V>
		typename std::enable_if<!std::is_base_of<_Vertex2Option<V>, T>::value>::type
		enableState(GLenum state) const
		{

		}

		template <Vertex V>
		typename std::enable_if<std::is_base_of<_Vertex2Option<V>, T>::value>::type
		disableState(GLenum state) const
		{
			glDisableClientState(state);
		}

		template <Vertex V>
		typename std::enable_if<!std::is_base_of<_Vertex2Option<V>, T>::value>::type
		disableState(GLenum state) const
		{

		}

		T*		_buffer;
		size_t	_count;
		size_t	_alloc;
	};

	typedef Batch2<Vertex2t, GL_QUADS>	SpriteBatch;
}

#undef BATCH_SIZE
#endif
