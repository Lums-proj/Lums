/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    StaticSpriteBatch.cpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Graphics/StaticSpriteBatch.hpp>

using namespace lm;

StaticSpriteBatch::StaticSpriteBatch()
: texture(nullptr)
{

}

void
StaticSpriteBatch::draw(const Texture& texture, int atlas, Vector2f pos, Vector2f scale, Vector4f color, Vector2b flip)
{
    setTexture(&texture);
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

    vbo.push(pos.x, pos.y, frame.pos.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(pos.x + w, pos.y, frame.pos.x + frame.size.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(pos.x + w, pos.y + h, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(pos.x, pos.y, frame.pos.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(pos.x + w, pos.y + h, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(pos.x, pos.y + h, frame.pos.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
}

void
StaticSpriteBatch::draw(const Sprite& sprite)
{
    draw(sprite.texture(), sprite.atlas(), sprite.pos, sprite.scale, sprite.color, sprite.flip);
}

void
StaticSpriteBatch::draw(const Font& font, const char* text, Vector2f pos, Vector4f color)
{
    int i = 0;
    int c;
    const float height = font.glyph('|').height;

    while ((c = text[i++]))
    {
        const Glyph& g = font.glyph(c);
        const float baseline = pos.y - g.top + height;

        draw(font.texture(), c, {pos.x + g.left, baseline}, {1.f, 1.f}, color);
        pos.x += g.advance - g.kerning[i];
    }
}

void
StaticSpriteBatch::setTexture(const Texture* texture)
{
    this->texture = texture;
}

void
StaticSpriteBatch::send()
{
    vbo.send();
}

void
StaticSpriteBatch::flush()
{
    vbo.reset();
}

void
StaticSpriteBatch::render()
{
    texture->bind();
    vbo.draw(GL_TRIANGLES);
}

StaticSpriteBatch::~StaticSpriteBatch()
{

}
