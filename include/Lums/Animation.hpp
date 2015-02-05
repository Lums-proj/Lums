/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Animation.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_ANIMATION_HPP
#define LUMS_ANIMATION_HPP

#include <Lums/Image.hpp>
#include <Lums/GL.hpp>

namespace lm
{
	/**
	* This class defines an Animation.
	*/
	class Animation
	{
	public:
		Animation();
		void	loadFile(const std::string& filename, size_t wcount, size_t hcount, bool resource = true);

		size_t
		width() const
		{
			return _width;
		}

		size_t
		height() const
		{
			return _height;
		}

		size_t
		wcount() const
		{
			return _wcount;
		}

		size_t
		hcount() const
		{
			return _hcount;
		}

		const Image&
		image() const
		{
			return _image;
		}

	private:
		Image	_image;
		size_t	_width;
		size_t	_height;
		size_t	_wcount;
		size_t	_hcount;
	};
}

#endif