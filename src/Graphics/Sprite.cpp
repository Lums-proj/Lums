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

#include <LumsInclude/Graphics/Sprite.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/Graphics/Image.hpp>

using namespace lm;

Sprite::Sprite()
: pos(0.f, 0.f)
, scale(1.f, 1.f)
, color(1.f, 1.f, 1.f, 1.f)
, flip(false, false)
, _texture(nullptr)
, _baseFrame(0)
, _currentFrame(0)
, _length(1)
, _acc(0)
, _speed(0)
, _finished(false)
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
        if (_currentFrame + 1 == _baseFrame + _length)
        {
            if (!_loop)
                _finished = true;
            else
                _currentFrame = _baseFrame;
        }
        else
            _currentFrame++;
    }
}
