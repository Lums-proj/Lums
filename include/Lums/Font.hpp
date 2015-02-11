/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Font.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_FONT_HPP
#define LUMS_FONT_HPP

#include <Lums/ExportDll.hpp>
#include <Lums/GL.hpp>
#include <string>

namespace lm
{
    class Font
    {
    public:
        LUMS_EXPORTED Font();
        LUMS_EXPORTED Font(const Font&) = delete;
        LUMS_EXPORTED void    loadFile(const std::string& filename, float size, bool resource = true);
        LUMS_EXPORTED void    load(const std::string& font, float size);
        LUMS_EXPORTED void    puts(int x, int y, const std::string& str) const;
        LUMS_EXPORTED void    puts(int x, int y, const char* str) const;
        LUMS_EXPORTED void    printf(int x, int y, const char* format, ...) const;
        LUMS_EXPORTED ~Font();

    private:
        LUMS_EXPORTED void    loadGlyphes(void*, unsigned char*);
        GLuint  _texture;
        int     _width[128];
        int     _height[128];
        int     _x[128];
        int     _y[128];
        int     _left[128];
        int     _top[128];
        int     _advance[128];
    };
}

#endif
