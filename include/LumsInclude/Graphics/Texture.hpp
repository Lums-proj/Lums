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
#include <LumsInclude/Binary/BObject.hpp>

namespace lm
{
    class Image;

    /**
     * @brief A class representing a texture in the GPU
     */
    class Texture
    {
    public:
        /**
         * Create a texture
         */
        Texture();

        /**
         * Get the texture width
         * @return The texture width
         */
        float           width() const { return _width; }

        /**
         * Get the texture height
         * @return The texture height
         */
        float           height() const { return _height; }

        /**
         * Get the texture buffer width
         * @return The texture buffer width
         */
        float           bufferWidth() const { return _bufferWidth; }

        /**
         * Get the texture buffer height
         * @return The texture buffer height
         */
        float           bufferHeight() const { return _bufferHeight; }

        /**
         * Set the texture image.
         * @param image The image
         */
        void            setImage(Image& image);

        /**
         * Load the texture
         */
        void            load();

        /**
         * Unload the texture
         */
        void            unload();

        /**
         * Bind the texture
         */
        void            bind() const;

        /**
         * Add a rect to the texture atlas
         * @param rect The rect to be added
         */
        void            pushAtlas(const Rect2f& rect);

        /**
         * Cut the texture into equal parts
         * @param w the texture part width
         * @param h the texture part height
         */
        void            pushAtlas(int w, int h);

        void            pushAtlas(const std::string& path, bool resource = true);

        /**
         * Get a rect from the atlas
         * @param i The atlas index
         * @return The rect
         */
        const Rect2f&   atlas(std::size_t i) const;

        /**
         * Check wether a texture is loaded
         * @return true if the texture is loaded, false otherwise
         */
        bool            loaded() const;

        void            loadBinary(const BObject& object);

        /**
         * Texture dtor
         */
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
