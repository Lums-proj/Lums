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
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/OperatingSystem.hpp>

using namespace lm;

Image::Image()
: _width(0)
, _height(0)
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
    typedef void (Image::*imgptr_t)();

    static const std::map<std::string, imgptr_t> extFuncs = {
        {"png", &Image::loadFilePNG}
    };

    std::string ext = _path.substr(_path.find_last_of('.') + 1);

    if (extFuncs.find(ext) != extFuncs.end())
        (this->*(extFuncs.at(ext)))();
}

void
Image::setPath(const std::string path, bool resource)
{
    _path = resource ? resourcePath() + '/' + path : path;
}

void
Image::loadFilePNG()
{
    FILE*           f = fopen(_path.c_str(), "rb");
    png_byte        header[8];

    if (!f)
    {
        std::cerr << "PNG: Could not open file '" << _path << "'" << std::endl;
        return;
    }

    fread(header, 1, 8, f);
    if (png_sig_cmp(header, 0, 8))
        return;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, f);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int color;
    int bits;
    unsigned int w;
    unsigned int h;
    GLint format;

    png_get_IHDR(png_ptr, info_ptr, &w, &h, &bits, &color, NULL, NULL, NULL);

    switch (color)
    {
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;

        case PNG_COLOR_TYPE_PALETTE:
            format = GL_RGBA;
            png_set_packing(png_ptr);
            png_set_palette_to_rgb(png_ptr);
            break;

        default:
            std::cerr << "PNG: Invalid color : " << color << " (" << bits << " bits)" << std::endl;
            return;
    }

    _width = png_get_image_width(png_ptr, info_ptr);
    _height = png_get_image_height(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    int rows = png_get_rowbytes(png_ptr, info_ptr);
    rows += 3 - (rows - 1) % 4;

    png_byte* image = new png_byte[rows * _height];
    png_byte** image_ptr = new png_byte*[_height];

    for (size_t i = 0; i < _height; i++)
        image_ptr[i] = image + i * rows;

    png_read_image(png_ptr, image_ptr);

    delete [] image_ptr;

    fclose(f);
}

Image::~Image()
{

}
