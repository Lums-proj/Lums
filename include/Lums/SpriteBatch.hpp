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

#include <Lums/VertexArray.hpp>
#include <Lums/Image.hpp>
#include <Lums/Sprite.hpp>

#define LUMS_SB_SIZE (8192)
#define LUMS_SB_VERT ((LUMS_SB_SIZE) / 4)

namespace lm
{
    class SpriteBatch
    {
    public:
        SpriteBatch();
        void    begin();
        void    draw(const Image& image, int atlas = 0, lm::Vector2f pos = {0, 0}, lm::Vector2f scale = {1, 1}, lm::Vector2b flip = {false, false});

        void
        draw(const Sprite& sprite)
        {
            draw(sprite.image(), sprite.atlas(), sprite.pos, sprite.scale, sprite.flip);
        }

        void    end();
        ~SpriteBatch();

    private:
        void    flush();

        VertexArrayct<LUMS_SB_SIZE> _va;
        size_t                      _count;
        GLuint                      _texture;
    };
};

#endif