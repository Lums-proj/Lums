/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Image.cpp                                    &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <Lums/Image.h>
#include <Lums/OperatingSystem.h>
#include <SDL2/SDL_image.h>

using namespace lm;

Image::Image()
: _width(0), _height(0), _image(nullptr), _texture(0)
{

}

Image::Image(const Image& rhs)
: _width(rhs._width), _height(rhs._height), _image(nullptr)
{
    
    _image = SDL_CreateRGBSurface(0, _width, _height, 32,
                                  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_BlitSurface(rhs._image, 0, _image, 0);
    glGenTextures(1, &_texture);
}

Image::Image(Image&& rhs)
: _width(rhs._width), _height(rhs._height), _image(rhs._image), _texture(rhs._texture)
{
    rhs._image = nullptr;
}

Image&
Image::operator=(const Image& rhs)
{
    _width = rhs._width;
    _height = rhs._height;
    if (rhs._image)
    {
        _image = SDL_CreateRGBSurface(0, _width, _height, 32,
                                      0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        SDL_BlitSurface(rhs._image, 0, _image, 0);
    }
    return *this;
}

Image&
Image::operator=(Image&& rhs)
{
    _width = rhs._width;
    _height = rhs._height;
    _image = rhs._image;
    _texture = rhs._texture;
    rhs._image = nullptr;
    return *this;
}

void
Image::LoadFile(const std::string path, bool resource)
{
    std::string     file = resource ? resourcePath() + path : path;
    SDL_Surface*    tmp;

    if (_image)
        SDL_FreeSurface(_image);
    tmp = IMG_Load(file.c_str());
    _width = tmp->w;
    _height = tmp->h;
    _image = SDL_CreateRGBSurface(0, _width, _height, 32,
                                  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_BlitSurface(tmp, 0, _image, 0);
    SDL_FreeSurface(tmp);
}

Image
Image::FromFile(const std::string path)
{
    Image   a;

    a.LoadFile(path);
    return a;
}

Image::~Image()
{
    if (_image)
    {
        SDL_FreeSurface(_image);
        glDeleteTextures(1, &_texture);
    }
}
