/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ImageDescriptor.cpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/ImageDescriptor.hpp>

using namespace lm;

ImageDescriptor::ImageDescriptor(const char* path)
: _path(path)
, _customAtlas(false)
, _linear(true)
, _atlas({.normal.x = 1, .normal.y = 1})
{

}

ImageDescriptor&
ImageDescriptor::atlas(size_t x, size_t y)
{
	_customAtlas = false;
	_atlas.normal.x = x;
	_atlas.normal.y = y;
	return *this;
}

ImageDescriptor&
ImageDescriptor::atlas(const lm::Rect2i* rect, size_t n)
{
	_customAtlas = true;
	_atlas.custom.rect = rect;
	_atlas.custom.n = n;
	return *this;
}

ImageDescriptor&
ImageDescriptor::linear(bool b)
{
	_linear = b;
	return *this;
}

