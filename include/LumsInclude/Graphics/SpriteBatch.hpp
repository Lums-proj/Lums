/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SpriteBatch.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SPRITE_BATCH_HPP
#define LUMS_SPRITE_BATCH_HPP

#include <LumsInclude/Graphics/VertexBuffer.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Sprite.hpp>
#include <LumsInclude/Graphics/Font.hpp>

namespace lm
{
    class SpriteBatch
    {
    public:
        SpriteBatch();
        void    begin();
        void    draw(const Texture& texture, int atlas = 0, lm::Vector2f pos = {0, 0}, lm::Vector2f scale = {1, 1}, lm::Vector2b flip = {false, false});

        void
        draw(const Sprite& sprite)
        {
            draw(sprite.texture(), sprite.atlas(), sprite.pos, sprite.scale(), sprite.flip);
        }

        void    draw(const Font& font, const char* text, lm::Vector2f pos = {0, 0});
        void    end();
        ~SpriteBatch();

    private:
        void    flush();

        VertexBufferP2T2C4          _vbo;
        const Texture*              _texture;
    };
};

#endif