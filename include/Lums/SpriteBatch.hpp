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
        
        void
        draw(const Image& image)
        {
            draw(image, 0, 0);
        }

        void
        draw(const Image& image, float x, float y, int atlas = 0, float scale = 1)
        {
            draw(image, x, y, atlas, scale, scale);
        }

        void    draw(const Image& image, float x, float y, int atlas, float scaleX, float scaleY);
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