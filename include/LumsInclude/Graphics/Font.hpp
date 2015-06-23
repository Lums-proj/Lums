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
#include <LumsInclude/Binary/BValue.hpp>
#include <LumsInclude/Binary/BObject.hpp>

namespace lm
{
    /**
     * @cond
     */
    namespace Freetype
    {
        void init();
    }
    /**
     * @endcond
     */

    /**
     * @brief A struct describing a single character from a font
     */
    struct Glyph
    {
        /**
         * The glyph width
         */
        int width;

        /**
         * The glyph height
         */
        int height;

        /**
         * The glyph top displacement
         */
        int top;

        /**
         * The glyph left displacement
         */
        int left;

        /**
         * The distance between two consecutive glyphs on the x axis
         */
        float advance;

        /**
         * A kerning table
         */
        float kerning[128];
    };

    /**
     * @brief A class describing a font
     */
    class Font
    {
    public:
        /**
         * The number of glyphs in a font
         */
        enum { glyphCount = 128 };

        /**
         * Construct an empty font
         */
        Font();

        /**
         * Get the texture associated with the font.
         * @return A reference to the texture
         */
        const Texture&
        texture() const
        {
            return _texture;
        }

        /**
         * Extract a glyph from the font
         * @param i The glyph index
         * @return A reference to the glyph
         */
        const Glyph&
        glyph(int i) const
        {
            return _glyphs[i];
        }

        /**
         * Set the load path for the font
         * @param path The load path
         * @param resource If true, the path is relative to the resource path
         */
        void    setPath(const std::string& path, bool resource = true);

        /**
         * Set the font size in points
         * size The size
         */
        void    setSize(float size);

        /**
         * Load the font
         */
        void    load();

        /**
         * Unload the font
         */
        void    unload();

        /**
         * Check wether the font was loaded.
         * @return True if the font was loaded.
         */
        bool    loaded() const;

        void    loadBinary(const BObject& object);

        /**
         * Font dtor
         */
        ~Font();

    private:
        Texture     _texture;
        Glyph       _glyphs[glyphCount];
        std::string _path;
        float       _size;
    };
}

#endif
