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
	/**
     * @brief A class representing a dynamic batch of bidimensional graphical elements
     */
    class SpriteBatch : public StaticSpriteBatch
    {
    public:
    	/**
         * Begin the batch
         */
        void    begin();

        /**
         * End the batch
         */
        void    end();

     protected:
     	/**
         * Set the texture
         * @param texture The texture
         */
        void    setTexture(const Texture* texture);
    };
};

#endif
