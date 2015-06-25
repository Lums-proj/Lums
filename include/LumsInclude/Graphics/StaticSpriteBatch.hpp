/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    StaticSpriteBatch.hpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_STATIC_SPRITE_BATCH_HPP
#define LUMS_STATIC_SPRITE_BATCH_HPP

#include <LumsInclude/Graphics/VertexBuffer.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Sprite.hpp>
#include <LumsInclude/Graphics/Font.hpp>
#include <LumsInclude/ExportDll.hpp>

namespace lm
{
    /**
     * @brief A class representing a static batch of bidimensional graphical elements
     */
    class StaticSpriteBatch
    {
    public:
        /**
         * Create a static sprite batch
         */
        StaticSpriteBatch(GLenum hint = GL_STATIC_DRAW);

        /**
         * Draw a texture into the batch
         * @param texture The texture to be drawn
         * @param atlas The atlas
         * @param pos The screen position
         * @param scale The scale
         * @param color The color
         * @param flip The flip values
         */
        LUMS_EXPORTED void              draw(const Texture& texture,
                                             int atlas = 0,
                                             Vector3f pos = {0.f, 0.f, 0.f},
                                             Vector2f scale = {1.f, 1.f},
                                             Vector4f color = {1.f, 1.f, 1.f, 1.f},
                                             Vector2b flip = {false, false});

        /**
         * Draw a sprite into the batch
         * @param sprite The sprite
         */
        LUMS_EXPORTED void              draw(const Sprite& sprite);

        /**
         * Draw text into the batch
         * @param font The font
         * @param text The text to be rendererd
         * @param pos The text position
         * @param color The text color
         */
        LUMS_EXPORTED void              draw(const Font& font,
                                             const char* text,
                                             Vector3f pos = {0.f, 0.f, 0.f},
                                             Vector4f color = {1.f, 1.f, 1.f, 1.f});

        /**
         * Set the batch texture
         * @param texture The texture
         */
        LUMS_EXPORTED virtual void      setTexture(const Texture* texture);

        /**
         * Send the batch to the GPU
         */
        LUMS_EXPORTED void              send();

        /**
         * Flush the batch
         */
        LUMS_EXPORTED void              flush();

        /**
         * Render the batch
         */
        LUMS_EXPORTED void              render();

        /**
         * Sprite batch dtor
         */
        ~StaticSpriteBatch();

    protected:
        /**
         * A vertex buffer object
         */
        VertexBufferP3T2C4          vbo;

        /**
         * A texture
         */
        const Texture*              texture;
    };
};

#endif
