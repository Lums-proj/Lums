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

                std::memset(buffer + (y + j) * 4 * T_WIDTH + (x + k) * 4, byte, 4);
            }
        }
        _width[i] = face->glyph->bitmap.width;
        _height[i] = face->glyph->bitmap.rows;
        _x[i] = x;
        _y[i] = y;
        _left[i] = face->glyph->bitmap_left;
        _top[i] = face->glyph->bitmap_top;
        _advance[i] = face->glyph->advance.x;
        if (face->glyph->bitmap.rows > maxY)
            maxY = face->glyph->bitmap.rows;
        x += face->glyph->bitmap.width;
    }
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    delete [] buffer;
    glPopAttrib();
}

void
Font::load(const std::string& font, float size)
{
    std::string filename;
#if defined(__APPLE__)
    filename = std::string("/Library/Fonts/") + font;
#elif defined(WIN32) || defined(WIN64)
    filename = std::string("/Windows/Fonts/") + font;
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
    std::vector<GLdouble> t;

    y += _top['T'];

    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);
    v.reserve(std::strlen(str) * 16);
    for (size_t j = 0; str[j]; j++)
    {
        char i = str[j];

        x += _left[i];
        int ny = y - _top[i];

        v.push_back(x);
        v.push_back(ny);
        t.push_back(_x[i] / 1024.0);
        t.push_back(_y[i] / 1024.0);

        v.push_back(x + _width[i]);
        v.push_back(ny);
        t.push_back((_x[i] + _width[i]) / 1024.0);
        t.push_back(_y[i] / 1024.0);

        v.push_back(x + _width[i]);
        v.push_back(ny + _height[i]);
        t.push_back((_x[i] + _width[i]) / 1024.0);
        t.push_back((_y[i] + _height[i]) / 1024.0);

        v.push_back(x);
        v.push_back(ny + _height[i]);
        t.push_back(_x[i] / 1024.0);
        t.push_back((_y[i] + _height[i]) / 1024.0);

        x += (_advance[i] >> 6);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, &(v[0]));
    glTexCoordPointer(2, GL_DOUBLE, 0 * 2, &(t[0]));
    glDrawArrays(GL_QUADS, 0, std::strlen(str) * 4);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
}

Font::~Font()
{

}

