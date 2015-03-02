/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ImageDescriptor.hpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_IMAGE_DESCRIPTOR_HPP
#define LUMS_IMAGE_DESCRIPTOR_HPP

#include <Lums/Rect2.hpp>

namespace lm
{
	class ImageDescriptor
	{
		friend class Image;

		public:
			ImageDescriptor(const char* path);
			ImageDescriptor&		atlas(size_t x, size_t y);
			ImageDescriptor&		atlas(const lm::Rect2i* rects, size_t n);
			ImageDescriptor&		linear(bool b = true);

		private:
			const char*		_path;
			bool			_customAtlas;
			bool			_linear;
			union
			{
				struct
				{
					size_t		x;
					size_t		y;
				} normal;

				struct
				{
					const lm::Rect2i*	rect;
					size_t				n;
				} custom;
			} _atlas;
	};
}

#endif
