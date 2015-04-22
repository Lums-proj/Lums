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
SpriteBatch::draw(const Image& image, int atlas, lm::Vector2f pos, lm::Vector2f scale, lm::Vector2b flip)
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
    float w = frame.w * image.width() * scale.x;
    float h = frame.h * image.height() * scale.y;

    if (flip.x)
    {
        pos.x += w;
        w = -w;
    }
    else
        pos.x += frame.offX;

    if (flip.y)
    {
        pos.y += h;
        h = -h;
    }
    else
        pos.y += frame.offY;

    const float fcorx = 1.0f / image.width();
    const float fcory = 1.0f / image.height();

    frame.x += fcorx * 0.5f;
    frame.y += fcory * 0.5f;
    frame.w -= fcorx;
    frame.h -= fcory;

    _va.push(pos.x, pos.y, 1.0f, 1.0f, 1.0f, frame.x, frame.y);
    _va.push(pos.x + w, pos.y, 1.0f, 1.0f, 1.0f, frame.x + frame.w, frame.y);
    _va.push(pos.x + w, pos.y + h, 1.0f, 1.0f, 1.0f, frame.x + frame.w, frame.y + frame.h);
    _va.push(pos.x, pos.y + h, 1.0f, 1.0f, 1.0f, frame.x, frame.y + frame.h);
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
    glBindTexture(GL_TEXTURE_2D, _texture);
    _va.draw(GL_QUADS);
    _va.clear();
    _count = 0;
}
