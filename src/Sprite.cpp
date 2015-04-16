/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sprite.cpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Sprite.hpp>
#include <Lums/GL.hpp>
#include <Lums/Image.hpp>

using namespace lm;

Sprite::Sprite()
: _image(nullptr)
, _baseImage(0)
, _currentImage(0)
, _length(1)
, _acc(0)
, _speed(0)
, _finished(false)
{

}

Sprite::Sprite(Image& image, size_t state)
: _image(&image)
, _baseImage(state)
, _currentImage(state)
, _length(1)
, _acc(0)
, _speed(0)
{

}

void
Sprite::update()
{
    if (_finished)
        return;
    _acc++;
    if (_acc == _speed)
    {
        _acc = 0;
        if (_currentImage + 1 == _baseImage + _length)
        {
            if (!_loop)
                _finished = true;
            else
                _currentImage = _baseImage;
        }
        else
            _currentImage++;
    }
}
