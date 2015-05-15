/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Font.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                         1                                %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_FONT_HPP
#define LUMS_FONT_HPP

#include <LumsInclude/Graphics/Texture.hpp>

namespace lm
{
    namespace Freetype
    {
        void init();
    }

    struct Glyph
    {
        int width;
        int height;
        int top;
        int left;
        int advance;
    };

    class Font
    {
    public:
        enum { glyphCount = 128 };

        Font();
        void    setPath(const std::string& path, bool resource = true);
        void    setSize(float size);
        void    load();
        void    unload();
        const Texture&    texture() const { return _texture; }
        ~Font();

    private:
        Texture     _texture;
        Glyph       _glyphs[glyphCount];
        std::string _path;
        float       _size;
    };
}

#endif
