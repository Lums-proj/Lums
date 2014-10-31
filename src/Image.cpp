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
#include <SDL2_image/SDL_image.h>

using namespace lm;

Image::Image()
: _width(0), _height(0), _mem_width(0), _mem_height(0), _image(nullptr)
{
    
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
    _mem_width = std::pow(2, std::log2(_width));
    _mem_height = std::pow(2, std::log2(_height));
    _image = SDL_CreateRGBSurface(0, _mem_width, _mem_height, 32,
                                  0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_BlitSurface(tmp, 0, _image, 0);
    SDL_FreeSurface(tmp);
}

Image::~Image()
{
    if (_image)
        SDL_FreeSurface(_image);
}