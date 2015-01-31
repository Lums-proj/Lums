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
#include <png.h>
#include <Lums/Image.hpp>
#include <Lums/OperatingSystem.hpp>

using namespace lm;

Image::Image()
: _width(0)
, _height(0)
, _texture(0)
{

}

Image::Image(Image&& rhs)
: _width(rhs._width)
, _height(rhs._height)
, _texture(rhs._texture)
{
    rhs._texture = 0;
}

Image&
Image::operator=(Image&& rhs)
{
    _width = rhs._width;
    _height = rhs._height;
    _texture = rhs._texture;
    rhs._texture = 0;
    return *this;
}

Image&
Image::loadFile(const std::string path, bool resource)
{
    typedef Image& (Image::*imgptr_t)(std::string, bool);

    static const std::map<std::string, imgptr_t> extFuncs = {
        {"png", &Image::loadFilePNG}
    };

    std::string ext = path.substr(path.find_last_of('.') + 1);

    if (extFuncs.find(ext) != extFuncs.end())
        return (this->*(extFuncs.at(ext)))(path, resource);
    return *this;
}

/*
 * This is KLUDGE
 */

Image&
Image::loadFilePNG(const std::string path, bool resource)
{
    std::string     file = resource ? resourcePath() + path : path;
    unsigned char*  image;
    unsigned char** imageBuf;
    FILE*           f = fopen(file.c_str(), "rb");

    if (_texture)
        glDeleteTextures(1, &_texture);
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    //setjmp(png_jmpbuf(png_ptr));
    png_init_io(png_ptr, f);
    png_read_info(png_ptr, info_ptr);
    _width = png_get_image_width(png_ptr, info_ptr);
    _height = png_get_image_height(png_ptr, info_ptr);
    image = new unsigned char[4 * _width * _height];
    imageBuf = new unsigned char*[_height];
    for (size_t i = 0; i < _height; i++)
        imageBuf[i] = new unsigned char[4 * _width];
    png_read_image(png_ptr, imageBuf);
    for (size_t j = 0; j < _height; j++)
    {
        std::memcpy(image + _width * 4 * (_height - j - 1), imageBuf[j], _width * 4);
        delete [] imageBuf[j];
    }
    delete [] imageBuf;
    fclose(f);
    gen(image);
    return *this;
}

Image
Image::fromFile(const std::string path, bool resource)
{
    Image   a;

    a.loadFile(path, resource);
    return a;
}

Image::~Image()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

// private

void
Image::gen(unsigned char* img)
{
    glGenTextures(1, &_texture);
    linear();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    delete [] img;
}
