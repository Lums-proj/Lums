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

#include <Lums/GL.hpp>
#include <string>

namespace lm
{
    class Font
    {
    public:
        Font();
        void    loadFile(const std::string& filename, float size, bool resource = true);
        void    load(const std::string& font, float size);
        void    puts(const std::string& str, int x = 0, int y = 0) const;
        void    puts(const char* str, int x = 0, int y = 0) const;
        void    debug() const;
        ~Font();

    private:
        GLuint  _texture;
        int     _width[128];
        int     _height[128];
        int     _x[128];
        int     _y[128];
    };
}

#endif
