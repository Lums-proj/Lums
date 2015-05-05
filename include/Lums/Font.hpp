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

#if 0

#ifndef LUMS_FONT_HPP
#define LUMS_FONT_HPP

#include <Lums/ExportDll.hpp>
#include <Lums/GL.hpp>
#include <string>

namespace lm
{
    /**
     * The font class is an abstraction over the freeType library.
     * It provides hardware accelerated text rendering through OpenGL.
     */
    class Font
    {
    public:
        /**
         * Create an empty font.
         */
        LUMS_EXPORTED Font();

        LUMS_EXPORTED Font(const Font&) = delete;

        /**
         * Load a font file.
         * After a call to this method, the font can be used for rendering.
         * @param filename A path to the font file
         * @size The size of the font, in dots.
         * @resource Wether to look for the font in the resource folder. Defaults to true.
         */
        LUMS_EXPORTED void    loadFile(const std::string& filename, float size, bool resource = true);

        /**
         * Load a system font file.
         * Be warned, some systems may not have system fonts.
         * You are supposed to try multiple fonts, to be sure to match at least one.
         * @font The font name, including extension.
         * @size The font size, in dots.
         */
        LUMS_EXPORTED void    load(const std::string& font, float size);

        /**
         * Render text using the font.
         * In debug mode, an error is reported if the font cannot be used.
         * In release mode, trying to render text using a null font is undefined
         * behavior.
         * @param x Where to render text, x coord.
         * @param y Where to render text, y coord.
         * @param str The text to be rendered.
         */
        LUMS_EXPORTED void    puts(int x, int y, const std::string& str) const;

        /**
         * This is the same as Font::puts, overloaded for const char*.
         * @param x Where to render text, x coord.
         * @param y Where to render text, y coord.
         * @param str The text to be rendered.
         */
        LUMS_EXPORTED void    puts(int x, int y, const char* str) const;

        /**
         * Render formated text. This function is equivalent to the libc printf.
         * This function behaves like Font::puts, except for the format.
         * @param x Where to render text, x coord.
         * @param y Where to render text, y coord.
         * @param format A printf-compatible format string.
         */
        LUMS_EXPORTED void    printf(int x, int y, const char* format, ...) const;

        /**
         * Destructor
         */
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
#endif
