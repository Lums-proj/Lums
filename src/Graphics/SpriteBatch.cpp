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

#include <LumsInclude/Graphics/SpriteBatch.hpp>

using namespace lm;

SpriteBatch::SpriteBatch()
{

}

void
SpriteBatch::begin()
{
    _texture = 0;
}

void
SpriteBatch::draw(const Texture& texture, int atlas, lm::Vector2f pos, lm::Vector2f scale, lm::Vector2b flip)
{
    if (!_texture)
    {
        _texture = &texture;
    }
    else if (_texture != &texture)
    {
        flush();
        _texture = &texture;
    }

    Rect2f frame = texture.atlas(atlas);
    float w = frame.size.x * texture.width() * scale.x;
    float h = frame.size.y * texture.height() * scale.y;

    if (flip.x)
    {
        pos.x += w;
        w = -w;
    }

    if (flip.y)
    {
        pos.y += h;
        h = -h;
    }

    const float fcorx = 1.0f / texture.bufferWidth();
    const float fcory = 1.0f / texture.bufferHeight();

    frame.pos.x += fcorx * 0.5f;
    frame.pos.y += fcory * 0.5f;
    frame.size.x -= fcorx;
    frame.size.y -= fcory;

    // We create two triangles from a single quad

    _vbo.push(pos.x, pos.y, frame.pos.x, frame.pos.y, 1.f, 1.f, 1.f, 1.f);
    _vbo.push(pos.x + w, pos.y, frame.pos.x + frame.size.x, frame.pos.y, 1.f, 1.f, 1.f, 1.f);
    _vbo.push(pos.x + w, pos.y + h, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, 1.f, 1.f, 1.f, 1.f);
    _vbo.push(pos.x, pos.y, frame.pos.x, frame.pos.y, 1.f, 1.f, 1.f, 1.f);
    _vbo.push(pos.x + w, pos.y + h, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, 1.f, 1.f, 1.f, 1.f);
    _vbo.push(pos.x, pos.y + h, frame.pos.x, frame.pos.y + frame.size.y, 1.f, 1.f, 1.f, 1.f);
}

void
SpriteBatch::draw(const Font& font, const char* text, lm::Vector2f pos)
{
    int i = 0;
    int c;
    const float height = font.glyph('|').height;

    while ((c = text[i++]))
    {
        const Glyph& g = font.glyph(c);
        const float baseline = pos.y - g.top + height;

        draw(font.texture(), c, {pos.x, baseline});
        pos.x += g.advance - g.kerning[i];
    }
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
    _texture->bind();
    _vbo.send();
    _vbo.draw(GL_TRIANGLES);
    _vbo.reset();
}
