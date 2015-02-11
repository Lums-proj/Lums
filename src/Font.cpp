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

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
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
    FT_Set_Char_Size(face, 0, static_cast<FT_F26Dot6>(size * 64), 0, 0);
    unsigned char* buffer = new unsigned char[T_WIDTH * T_WIDTH * 4];
    std::memset(buffer, 0, T_WIDTH * T_WIDTH * 4);
    loadGlyphes(face, buffer);
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, T_WIDTH, T_WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glPopAttrib();
    delete [] buffer;
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
Font::puts(int x, int y, const std::string& str) const
{
    Font::puts(x, y, str.c_str());
}

void
Font::puts(int x, int y, const char* str) const
{
    std::vector<GLdouble> v;

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

        v.push_back(_x[i] / 1024.0);
        v.push_back(_y[i] / 1024.0);
        v.push_back(x);
        v.push_back(ny);

        v.push_back((_x[i] + _width[i]) / 1024.0);
        v.push_back(_y[i] / 1024.0);
        v.push_back(x + _width[i]);
        v.push_back(ny);

        v.push_back((_x[i] + _width[i]) / 1024.0);
        v.push_back((_y[i] + _height[i]) / 1024.0);
        v.push_back(x + _width[i]);
        v.push_back(ny + _height[i]);

        v.push_back(_x[i] / 1024.0);
        v.push_back((_y[i] + _height[i]) / 1024.0);
        v.push_back(x);
        v.push_back(ny + _height[i]);

        x += (_advance[i] >> 6);
    }
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_DOUBLE, sizeof(GLdouble) * 4, &(v[0]));
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, sizeof(GLdouble) * 4, &(v[2]));
    glDrawArrays(GL_QUADS, 0, std::strlen(str) * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopAttrib();
}

void
Font::printf(int x, int y, const char* format, ...) const
{
    va_list ap;
    char* str;

    va_start(ap, format);
#if _MSC_VER
    str = static_cast<char*>(malloc(_vscprintf(format, ap) + 1));
    vsprintf(str, format, ap);
#elif
    vasprintf(&str, format, ap);
#endif
    Font::puts(x, y, str);
    free(str);
    va_end(ap);
}

Font::~Font()
{

}

// private

void
Font::loadGlyphes(void* faceHandle, unsigned char* buffer)
{
    size_t x = 0, y = 0, yMax = 0;
    FT_Face face = static_cast<FT_Face>(faceHandle);
    FT_GlyphSlot g = face->glyph;
    for (int i = 0; i < 128; i++)
    {
        FT_Load_Char(face, i, FT_LOAD_RENDER);
        if (x + g->bitmap.width > T_WIDTH)
        {
            x = 0;
            y += yMax;
            yMax = 0;
        }
        for (size_t j = 0; j < g->bitmap.rows; j++)
        {
            for (size_t k = 0; k < g->bitmap.width; k++)
            {
                size_t index = j * g->bitmap.pitch + k;
                unsigned char byte = *(static_cast<unsigned char*>(g->bitmap.buffer) + index);
                std::memset(buffer + (y + j) * 4 * T_WIDTH + (x + k) * 4, byte, 4);
            }
        }
        _width[i] = g->bitmap.width;
        _height[i] = g->bitmap.rows;
        _x[i] = x;
        _y[i] = y;
        _left[i] = g->bitmap_left;
        _top[i] = g->bitmap_top;
        _advance[i] = g->advance.x;
        if (g->bitmap.rows > yMax)
            yMax = g->bitmap.rows;
        x += g->bitmap.width;
    }
}
