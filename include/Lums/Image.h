/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GameState.h                                  &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_IMAGE_H
#define LUMS_IMAGE_H

#include <SDL2/SDL.h>
#include <Lums/GL.h>
#include <string>

namespace lm
{
    /**
     * This class represents an Image, stored in the most efficient way speed-wise.
     */
    class Image
    {
    public:

        /**
         * Create an empty Image.
         */
        Image();

        Image(const Image&) = delete;

        /**
         * Move-copy an Image.
         * @param rhs The image to be moved from.
         */
        Image(Image&& rhs);
        Image&          operator=(const Image&) = delete;
        Image&          operator=(Image&&);
        
        void
        Bind() const
        {
            glBindTexture(GL_TEXTURE_2D, _texture);
        }

        GLuint
        Texture() const
        {
            return _texture;
        }

        bool
        Valid() const
        {
            return _texture != 0;
        }

        int
        Width() const
        {
            return _width;
        }

        int
        Height() const
        {
            return _height;
        }

        void            LoadFile(const std::string path, bool resource = true);
        static Image    FromFile(const std::string path);
        ~Image();
    private:
        void            Gen(SDL_Surface* surface);
        int             _width;
        int             _height;
        GLuint          _texture;
    };
}

#endif