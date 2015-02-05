/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Animation.cpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Animation.hpp>

using namespace lm;

Animation::Animation()
: _width(0)
, _height(0)
, _wcount(0)
, _hcount(0)
{

}

void
Animation::loadFile(const std::string& filename, size_t wcount, size_t hcount, bool resource)
{
	_image.loadFile(filename, resource);
	_wcount = wcount;
	_hcount = hcount;
	_width = _image.width() / wcount;
	_height = _image.height() / hcount;
}

