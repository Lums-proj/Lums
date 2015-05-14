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

using namespace lm;

Texture::Texture()
{
    glGenTextures(1, &_texture);
}

void
Texture::setImage(Image& image)
{
    _image = &image;
}

void
Texture::load()
{

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
    const float fw = w / _width;
    const float fh = h / _height;
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; i++)
            pushAtlas({{i * fw, j * fw}, {fw, fh}});
    }
}

const Rect2f&
Texture::atlas(std::size_t i) const
{
    return _atlas[i];
}


Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}
