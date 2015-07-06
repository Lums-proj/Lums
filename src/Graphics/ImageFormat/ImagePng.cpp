/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ImagePng.cpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <png.h>
#include <LumsInclude/Graphics/Image.hpp>

using namespace lm;

unsigned char*
ImageFormat::png(FILE* file, unsigned int& width, unsigned int& height, GLenum& format)
{
    png_byte header[8];

    fread(header, 1, 8, file);
    if (png_sig_cmp(header, 0, 8))
    {
        std::cerr << "Invalid png signature" << std::endl;
        return nullptr;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int color;
    int bits;

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bits, &color, nullptr, nullptr, nullptr);

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
            return nullptr;
    }

    png_read_update_info(png_ptr, info_ptr);

    int rows = png_get_rowbytes(png_ptr, info_ptr);
    rows += 3 - (rows - 1) % 4;

    png_byte* image = new png_byte[rows * height];
    png_byte** image_ptr = new png_byte*[height];

    for (unsigned int i = 0u; i < height; i++)
        image_ptr[i] = image + i * rows;

    png_read_image(png_ptr, image_ptr);
    
    delete [] image_ptr;

    return image;
}

