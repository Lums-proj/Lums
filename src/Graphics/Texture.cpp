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

#include <LumsInclude/OperatingSystem.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/Binary/BArray.hpp>

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
}

void
Texture::pushAtlas(const std::string& path, bool resource)
{
    std::string fpath = resource ? resourcePath() + path : path;
    std::ifstream f(fpath);

    uint32_t len;
    f.read((char*)&len, 4);
    for (unsigned i = 0; i < len; ++i)
    {
        Rect2f rect;
        f.read((char*)&rect.pos.x, 4);
        f.read((char*)&rect.pos.y, 4);
        f.read((char*)&rect.size.x, 4);
        f.read((char*)&rect.size.y, 4);
        pushAtlas(rect);
    }
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

void
Texture::loadBinary(const BObject& object)
{
    _image = new lm::Image;
    char* path = object["path"].asString();
    auto& atlas = object["atlas"];
    if (atlas.isArray())
    {
        int atlasWidth = atlas.asArray()[0].asInt();
        int atlasHeight = atlas.asArray()[1].asInt();
        pushAtlas(atlasWidth, atlasHeight);
    }
    else if (atlas.isString())
        pushAtlas(atlas.asString(), true);
    _image->setPath(path, true);
}

Texture::~Texture()
{
    unload();
}
