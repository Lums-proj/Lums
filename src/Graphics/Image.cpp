/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Image.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <cmath>
#include <iostream>
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/OperatingSystem.hpp>

using namespace lm;

Image::Image()
: _width(0u)
, _height(0u)
, _data(nullptr)
{

}

Image::Image(Image&& rhs)
: _width(rhs._width)
, _height(rhs._height)
, _path(rhs._path)
{

}

Image&
Image::operator=(Image&& rhs)
{
    _width = rhs._width;
    _height = rhs._height;
    _path = rhs._path;
    return *this;
}

void
Image::load()
{
    FILE* file = fopen(_path.c_str(), "r");

    unload();

    if (!file)
    {
        std::cerr << "Image: could not open " << _path << std::endl;
        return;
    }
    _data = ImageFormat::png(file, _width, _height, _format);
    fclose(file);
}

void
Image::unload()
{
    delete [] _data;
    _data = nullptr;
}

void
Image::setPath(const std::string path, bool resource)
{
    _path = resource ? resourcePath() + '/' + path : path;
}

void
Image::setBuffer(unsigned char* buffer, unsigned int w, unsigned int h, GLenum format)
{
    unload();
    _data = buffer;
    _width = w;
    _height = h;
    _format = format;
}

Image::~Image()
{
    unload();
}
