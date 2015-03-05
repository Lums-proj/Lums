/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SpriteBatch.cpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/SpriteBatch.hpp>
#include <iostream>

using namespace lm;

SpriteBatch::SpriteBatch()
{

}

void
SpriteBatch::begin()
{
    _count = 0;
    _texture = 0;
    _va.clear();
}

void
SpriteBatch::draw(const Image& image, float x, float y, int atlas, float scaleX, float scaleY)
{
    if (!_texture)
    {
        _texture = image.texture();
    }
    else if (_texture != image.texture())
    {
        flush();
        _texture = image.texture();
    }
    if (_count >= LUMS_SB_VERT)
    {
        flush();
    }

    FrameDescriptorf frame = image.atlasAt(atlas);
    float w = frame.w * image.width() * scaleX;
    float h = frame.h * image.height() * scaleY;

    x += frame.offX;
    y += frame.offY;
    _va.push(x, y, 1.0f, 1.0f, 1.0f, frame.x, frame.y);
    _va.push(x + w, y, 1.0f, 1.0f, 1.0f, frame.x + frame.w, frame.y);
    _va.push(x + w, y + h, 1.0f, 1.0f, 1.0f, frame.x + frame.w, frame.y + frame.h);
    _va.push(x, y + h, 1.0f, 1.0f, 1.0f, frame.x, frame.y + frame.h);
    _count++;
}

void
SpriteBatch::end()
{
    flush();
}

SpriteBatch::~SpriteBatch()
{

}

/*
** PRIVATE
*/

void
SpriteBatch::flush()
{
    //std::cout << "Hi" << std::endl;
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);
    _va.draw(GL_QUADS);
    _va.clear();
    _texture = 0;
    _count = 0;
}
