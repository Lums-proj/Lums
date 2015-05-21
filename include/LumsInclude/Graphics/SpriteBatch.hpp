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

#include <LumsInclude/Graphics/StaticSpriteBatch.hpp>

namespace lm
{
    class SpriteBatch : public StaticSpriteBatch
    {
    public:
        void    begin();
        void    end();
        void    setTexture(const Texture* texture);
    };
};

#endif
