/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Font.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Lums/Font.hpp>
#include <Lums/OperatingSystem.hpp>
#include <iostream>

#define T_WIDTH 1024

using namespace lm;

static FT_Library library;

Font::Font()
: _texture(0)
{
    static bool loaded = false;

    if (!loaded)
    {
        FT_Init_FreeType(&library);
        loaded = true;
    }
}

void
Font::loadFile(const std::string& filename, float size, bool resource)
{
    std::string file = filename;
    FT_Face face;

    if (resource)
        file = resourcePath() + file;
    FT_New_Face(library, file.c_str(), 0, &face);
    FT_Set_Char_Size(face, 0, size * 64, 0, 0);

    unsigned char* buffer = new unsigned char[T_WIDTH * T_WIDTH * 4];
    std::memset(buffer, 0, T_WIDTH * T_WIDTH * 4);

    int x = 0;
    int y = 0;
    int maxY = 0;

    for (int i = 0; i < 128; i++)
    {
        FT_Load_Char(face, i, FT_LOAD_RENDER);
        if (x + face->glyph->bitmap.width > T_WIDTH)
        {
            x = 0;
            y += maxY;
            maxY = 0;
        }

        for (size_t j = 0; j < face->glyph->bitmap.rows; j++)
        {
            for (size_t k = 0; k < face->glyph->bitmap.width; k++)
            {
                unsigned char byte = *(static_cast<unsigned char*>(face->glyph->bitmap.buffer) + j * face->glyph->bitmap.pitch + k);

                std::memset(buffer + (y + j) * 4 * T_WIDTH + x + k, byte, 4);
            }
        }
        _width[i] = face->glyph->bitmap.width;
        _height[i] = face->glyph->bitmap.rows;
        _x[i] = x;
        _y[i] = y;
        if (face->glyph->bitmap.rows > maxY)
            maxY = face->glyph->bitmap.rows;
        x += face->glyph->bitmap.width;
    }
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    delete [] buffer;
}

void
Font::load(const std::string& font, float size)
{
    std::string filename;
#ifdef __APPLE__
    filename = std::string("/Library/Fonts/") + font;
#endif
    loadFile(filename, size, false);
}

void
Font::puts(const std::string& str, int x, int y) const
{
    Font::puts(str.c_str(), x, y);
}

void
Font::puts(const char* str, int x, int y) const
{
    std::vector<GLdouble> v;

    glBindTexture(GL_TEXTURE_2D, _texture);
    v.reserve(std::strlen(str) * 16);
    for (size_t j = 0; str[j]; j++)
    {
        char i = str[j];

        v.push_back(x);
        v.push_back(y);
        v.push_back(_x[i] / 1024.0);
        v.push_back(_y[i] / 1024.0);

        v.push_back(x + _width[i]);
        v.push_back(y);
        v.push_back((_x[i] + _width[i]) / 1024.0);
        v.push_back(_y[i] / 1024.0);

        v.push_back(x + _width[i]);
        v.push_back(y + _height[i]);
        v.push_back((_x[i] + _width[i]) / 1024.0);
        v.push_back((_y[i] + _height[i]) / 1024.0);

        v.push_back(x);
        v.push_back(y + _height[i]);
        v.push_back(_x[i] / 1024.0);
        v.push_back((_y[i] + _height[i]) / 1024.0);

        x += _width[i];

        std::cout << "Letter : " << i << " dim " << _width[i] << ' ' << _height[i] << ' ' << _x[i] << ' ' << _y[i] << '\n'; 
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_DOUBLE, sizeof(GLdouble) * 2, &(v[0]));
    glTexCoordPointer(2, GL_DOUBLE, sizeof(GLdouble) * 2, &(v[2]));
    glDrawArrays(GL_QUADS, 0, std::strlen(str) * 4);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
Font::debug() const
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex2i(0, 0);
    glTexCoord2d(1, 0);
    glVertex2i(200, 0);
    glTexCoord2d(1, 1);
    glVertex2i(200, 200);
    glTexCoord2d(0, 1);
    glVertex2i(0, 200);
    glEnd();
}

Font::~Font()
{

}
