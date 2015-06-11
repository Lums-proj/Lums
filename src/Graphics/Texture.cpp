/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Texture.cpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Image.hpp>
#include <iostream>

using namespace lm;

Texture::Texture()
: _texture(0)
{

}

void
Texture::setImage(Image& image)
{
    _image = &image;
}

void
Texture::load()
{
    const bool loaded = _image->loaded();

    unload();
    if (!loaded)
        _image->load();
    glGenTextures(1, &_texture);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, _image->format(), _image->bufferWidth(), _image->bufferHeight(), 0, _image->format(), GL_UNSIGNED_BYTE, _image->data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _width = _image->width();
    _height = _image->height();
    _bufferWidth = _image->bufferWidth();
    _bufferHeight = _image->bufferHeight();
    if (!loaded)
        _image->unload();
}

void
Texture::unload()
{
    if (!_texture)
        return;
    glDeleteTextures(1, &_texture);
    _texture = 0;
}

void
Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, _texture);
}

void         
Texture::pushAtlas(const Rect2f& rect)
{
    _atlas.push_back(rect);
}

void         
Texture::pushAtlas(int w, int h)
{
    const float fw = 1.f / w;
    const float fh = 1.f / h;

    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
            pushAtlas({{i * fw, j * fh}, {fw, fh}});
    }
    if (_image)
        _image->setScaleHint(w, h);
}

const Rect2f&
Texture::atlas(std::size_t i) const
{
    return _atlas[i];
}

bool
Texture::loaded() const
{
    return _texture != 0;
}

Texture::~Texture()
{
    unload();
}
