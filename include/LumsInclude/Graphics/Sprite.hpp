/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sprite.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SPRITE_HPP
#define LUMS_SPRITE_HPP

#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/ExportDll.hpp>
#include <LumsInclude/Math/Vector.hpp>
#include <iostream>

namespace lm
{
    /**
     * @brief A class representing a sprite
     */
    class Sprite
    {
    public:
        /**
         * Create a sprite
         */
        Sprite();

        /**
         * Get the texture from the sprite.
         * @return The texture
         */
        Texture&
        texture() const
        {
            return *_texture;
        }

        /**
         * Get the sprite width
         * @return The width
         */
        int
        width() const
        {
            return _texture->atlas(_currentFrame).size.x * _texture->width() * scale.x;
        }

        /**
         * Get the sprite height
         * @return The height
         */
        int
        height() const
        {
            return _texture->atlas(_currentFrame).size.y * _texture->height() * scale.y;
        }

        /**
         * Get the sprite current atlas frame
         * @return An atlas frame
         */
        std::size_t
        atlas() const
        {
            return _currentFrame;
        }

        /**
         * Get the sprite frame relative to the animation
         * @return the animation frame
         */
        int
        frame() const
        {
            return _currentFrame - _baseFrame;
        }

        /**
         * Set the sprite texture
         * @param texture The texture
         */
        void
        setTexture(Texture& texture)
        {
            _texture = &texture;
            setImageInAtlas(0);
        }

        /**
         * Set the frame animation
         * @param image The base image atlas
         * @param length The animation length
         * @param speed The animation speed, in 120 frame ticks
         * @param loop If true, the animation loops
         */
        void
        setAnimation(std::size_t image, std::size_t length, std::size_t speed, bool loop = true)
        {
            setSpeed(speed);
            _length = length;
            _loop = loop;
            _finished = false;
            setImageInAtlas(image);
        }

        /**
         * Set the animation speed
         * @param speed The speed
         */
        void
        setSpeed(std::size_t speed)
        {
            _acc = 0;
            _speed = speed;
        }

        /**
         * Set the current image in atlas
         * @param i The image index
         */
        void
        setImageInAtlas(std::size_t i)
        {
            _baseFrame = _currentFrame = i;
            _acc = 0;
        }

        /**
         * Check if the animation has ended
         * @return true if the animation is over
         */
        bool
        finished() const
        {
            return _finished;
        }

        /**
         * Update the sprite
         */
        LUMS_EXPORTED void  update();

        /**
         * The sprite position
         */
        Vector3f    pos;

        /**
         * The sprite scale
         */
        Vector2f    scale;

        /**
         * The sprite color
         */
        Vector4f    color;

        /**
         * The sprite flip value
         */
        Vector2b    flip;

    private:
        Texture*        _texture;
        size_t          _baseFrame;
        size_t          _currentFrame;
        size_t          _length;
        size_t          _acc;
        size_t          _speed;
        bool            _loop;
        bool            _finished;

    };
}

#endif
