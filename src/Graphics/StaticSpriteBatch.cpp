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

#include <cmath>
#include <LumsInclude/Graphics/StaticSpriteBatch.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>

using namespace lm;

#ifdef M_PI
# undef M_PI
#endif

#define M_PI 3.14159265358979323846f

StaticSpriteBatch::StaticSpriteBatch(GLenum hint)
: vbo(hint)
, texture(nullptr)
{

}

void
StaticSpriteBatch::draw(const Texture& texture, int atlas, Vector3f pos, Vector2f scale, Vector2f rotOrigin, float rotation, Vector4f color, Vector2b flip)
{
    lm::Vector2f points[4];

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

    float sinx = sin(rotation * M_PI / 180.f);
    float cosx = cos(rotation * M_PI / 180.f);

    points[0] = { cosx * (pos.x - rotOrigin.x) - sinx * (pos.y - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x - rotOrigin.x) + cosx * (pos.y - rotOrigin.y) + rotOrigin.y };
    points[1] = { cosx * (pos.x + w - rotOrigin.x) - sinx * (pos.y - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x + w - rotOrigin.x) + cosx * (pos.y - rotOrigin.y) + rotOrigin.y };
    points[2] = { cosx * (pos.x + w - rotOrigin.x) - sinx * (pos.y + h - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x + w - rotOrigin.x) + cosx * (pos.y + h - rotOrigin.y) + rotOrigin.y };
    points[3] = { cosx * (pos.x - rotOrigin.x) - sinx * (pos.y + h - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x - rotOrigin.x) + cosx * (pos.y + h - rotOrigin.y) + rotOrigin.y };

    // const float fcorx = 1.0f / texture.bufferWidth();
    // const float fcory = 1.0f / texture.bufferHeight();

    // frame.pos.x += fcorx * 0.5f;
    // frame.pos.y += fcory * 0.5f;
    // frame.size.x -= fcorx;
    // frame.size.y -= fcory;

    // We create two triangles from a single quad

    vbo.push(points[0].x, points[0].y, pos.z, frame.pos.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(points[1].x, points[1].y, pos.z, frame.pos.x + frame.size.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(points[2].x, points[2].y, pos.z, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(points[0].x, points[0].y, pos.z, frame.pos.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(points[2].x, points[2].y, pos.z, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(points[3].x, points[3].y, pos.z, frame.pos.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
}

void
StaticSpriteBatch::draw(const Sprite& sprite)
{
    draw(sprite.texture(), sprite.atlas(), sprite.pos, sprite.scale, sprite.color, sprite.flip);
}

void
StaticSpriteBatch::draw(const Font& font, const char* text, Vector3f pos, Vector4f color)
{
    int i = 0;
    int c;
    const float height = font.glyph('|').height;

    while ((c = text[i++]))
    {
        const Glyph& g = font.glyph(c);
        const float baseline = pos.y - g.top + height;

        draw(font.texture(), c, {pos.x + g.left, baseline, pos.z}, {1.f, 1.f}, color);
        pos.x += g.advance - g.kerning[i];
    }
}

static void
applyMatrixTrasform(Matrix4f& mat, const Skeleton& skeleton, int bone)
{
    const Bone& b = skeleton.bones()[bone];
    int parent = b.parent();
    if (parent != -1)
        applyMatrixTrasform(mat, skeleton, parent);
    Vector4f nullPoint = {0.f, 0.f, 0.f, 1.f};
    nullPoint = mat * nullPoint;
    Vector3f origin = { nullPoint.x, nullPoint.y, 0 };
    Vector3f pos = { b.position().x, b.position().y, 0 };
    translate(mat, pos);
    translate(mat, -origin);
    rotate(mat, b.rotation(), { 0.f, 0.f, 1.f });
    translate(mat, origin);
}

void
StaticSpriteBatch::draw(const Skeleton& skeleton, const Texture& texture, Vector3f pos)
{
    for (auto& skin : skeleton.skins())
    {
        Matrix4f mat = Matrix4f::identity();
        applyMatrixTrasform(mat, skeleton, skin.bone());
        
        Vector4f nullPoint = { 0.f, 0.f, 0.f, 1.f };
        nullPoint = mat * nullPoint;
        Vector3f origin = { nullPoint.x, nullPoint.y, 0.f };
        Vector3f sPos = { skin.position().x, skin.position().y, 0 };

        translate(mat, sPos);
        translate(mat, -origin);
        rotate(mat, skin.rotation(), { 0.f, 0.f, 1.f });
        translate(mat, origin);
        translate(mat, pos);

        draw(texture, skin.texture(), mat);
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
    if (!texture)
        return;
    texture->bind();
    vbo.draw(GL_TRIANGLES);
}

StaticSpriteBatch::~StaticSpriteBatch()
{

}
