/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Texture.hpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_TEXTURE_HPP
#define LUMS_TEXTURE_HPP

#include <cstdint>
#include <vector>
#include <LumsInclude/Math/Rect.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>

namespace lm
{
    class Image;

    class Texture
    {
    public:
        Texture();

        float           width() const { return _width; }
        float           height() const { return _height; }
        float           bufferWidth() const { return _bufferWidth; }
        float           bufferHeight() const { return _bufferHeight; }

        void            setImage(Image& image);
        void            load();
        void            unload();
        void            bind() const;
        void            pushAtlas(const Rect2f& rect);
        void            pushAtlas(int w, int h);
        const Rect2f&   atlas(std::size_t i) const;
        bool            loaded() const;
        ~Texture();

    private:
        GLuint              _texture;
        Image*              _image;
        float               _width;
        float               _height;
        float               _bufferWidth;
        float               _bufferHeight;
        std::vector<Rect2f> _atlas;
    };
}

#endif
