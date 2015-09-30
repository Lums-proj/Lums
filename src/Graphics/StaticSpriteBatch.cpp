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

#include <iostream>
#include <cmath>
#include <LumsInclude/Graphics/StaticSpriteBatch.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/Graphics/Graphics.hpp>

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
StaticSpriteBatch::draw(const Texture& texture, int atlas, Vector3f quad[4], Vector4f color, Vector2b flip)
{
    setTexture(&texture);
    Rect2f frame = texture.atlas(atlas);
    if (flip.x)
    {
        frame.pos.x += frame.size.x;
        frame.size.x *= -1;
    }
    if (flip.y)
    {
        frame.pos.y += frame.size.y;
        frame.size.y *= -1;
    }

    Vector2f bufferSize = {texture.bufferWidth(), texture.bufferHeight()};
    Vector2f texelSize = {1 / bufferSize.x, 1 / bufferSize.y};
    frame.pos.x += texelSize.x / 2;
    frame.pos.y += texelSize.y / 2;
    frame.size.x -= texelSize.x;
    frame.size.y -= texelSize.y;

    vbo.push(quad[0].x, quad[0].y, quad[0].z, frame.pos.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(quad[1].x, quad[1].y, quad[1].z, frame.pos.x + frame.size.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(quad[2].x, quad[2].y, quad[2].z, frame.pos.x + frame.size.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(quad[0].x, quad[0].y, quad[0].z, frame.pos.x, frame.pos.y + frame.size.y, color[0], color[1], color[2], color[3]);
    vbo.push(quad[2].x, quad[2].y, quad[2].z, frame.pos.x + frame.size.x, frame.pos.y, color[0], color[1], color[2], color[3]);
    vbo.push(quad[3].x, quad[3].y, quad[3].z, frame.pos.x, frame.pos.y, color[0], color[1], color[2], color[3]);
}

void
StaticSpriteBatch::draw(const Texture& texture, int atlas, const Matrix4f& mat, Vector4f color)
{
    lm::Vector3f quad[4];

    Rect2f frame = texture.atlas(atlas);
    float w = frame.size.x * texture.width();
    float h = frame.size.y * texture.height();

    auto q0 = mat * Vector4f(0.f, 0.f, 0.f, 1.0f);
    auto q1 = mat * Vector4f(w, 0.f, 0.f, 1.0f);
    auto q2 = mat * Vector4f(w, h, 0.f, 1.0f);
    auto q3 = mat * Vector4f(0.f, h, 0.f, 1.0f);

    quad[0] = { q0.x, q0.y, q0.z };
    quad[1] = { q1.x, q1.y, q1.z };
    quad[2] = { q2.x, q2.y, q2.z };
    quad[3] = { q3.x, q3.y, q3.z };

    draw(texture, atlas, quad, color, {false, false});
}

void
StaticSpriteBatch::draw(const Texture& texture, int atlas, Vector3f pos, Vector2f scale, Vector2f rotOrigin, float rotation, Vector4f color, Vector2b flip)
{
    lm::Vector3f quad[4];

    Rect2f frame = texture.atlas(atlas);
    float w = frame.size.x * texture.width() * scale.x;
    float h = frame.size.y * texture.height() * scale.y;

    float sinx = sin(rotation * M_PI / 180.f);
    float cosx = cos(rotation * M_PI / 180.f);

    quad[0] = { cosx * (pos.x - rotOrigin.x) - sinx * (pos.y - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x - rotOrigin.x) + cosx * (pos.y - rotOrigin.y) + rotOrigin.y, pos.z };
    quad[1] = { cosx * (pos.x + w - rotOrigin.x) - sinx * (pos.y - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x + w - rotOrigin.x) + cosx * (pos.y - rotOrigin.y) + rotOrigin.y, pos.z };
    quad[2] = { cosx * (pos.x + w - rotOrigin.x) - sinx * (pos.y + h - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x + w - rotOrigin.x) + cosx * (pos.y + h - rotOrigin.y) + rotOrigin.y, pos.z };
    quad[3] = { cosx * (pos.x - rotOrigin.x) - sinx * (pos.y + h - rotOrigin.y) + rotOrigin.x,
        sinx * (pos.x - rotOrigin.x) + cosx * (pos.y + h - rotOrigin.y) + rotOrigin.y, pos.z };

    draw(texture, atlas, quad, color, flip);
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
    float hCoeff = 1.f / globalScale();

    while ((c = text[i++]))
    {
        const Glyph& g = font.glyph(c);

        draw(font.texture(), c, {pos.x + g.left, pos.y + (g.top - g.height) * hCoeff, pos.z}, {1.f, 1.f}, color);
        pos.x += g.advance - g.kerning[i];
    }
}

void
StaticSpriteBatch::draw(const Skeleton& skeleton, const Texture& texture, Vector3f pos, Vector4f color)
{
    for (auto& slot : skeleton.slots)
    {
        int attachmentIndex = slot.attachment;

        if (attachmentIndex == -1)
            continue;

        const Bone& bone = skeleton.bones[slot.bone];

        const Attachment& att = skeleton.attachments[attachmentIndex];
        Rect2f frame = texture.atlas(att.texture);
        float w = frame.size.x * texture.width();
        float h = frame.size.y * texture.height();

        Matrix4f mat = Matrix4f::identity();
        translate(mat, { -w / 2.f, -h / 2.f, 0 });
        rotate(mat, att.rotation, { 0, 0, 1 });
        translate(mat, { att.position.x, att.position.y, 0});
        bone.transform(mat);
        if (skeleton.flip())
        {
            Matrix4f flipMat = Matrix4f::identity();
            flipMat[0][0] = -1.f;
            mat *= flipMat;
        }
        translate(mat, pos);
        draw(texture, att.texture, mat, color);
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
