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

        Image&  operator=(const Image&) = delete;

        /**
         * Move-copy an Image.
         * @param rhs The image to be moved from.
         */
        Image&  operator=(Image&& rhs);
        
        /**
         * Bind the image to the OpenGL context.
         */
        void
        Bind() const
        {
            glBindTexture(GL_TEXTURE_2D, _texture);
        }

        /**
         * Get the texture identifier.
         * @return A texture identifier, or 0 if the image is not valid.
         */
        GLuint
        Texture() const
        {
            return _texture;
        }

        /**
         * Check if the image is valid.
         * @return true if the image is valid.
         */
        bool
        Valid() const
        {
            return _texture != 0;
        }

        /**
         * Get the image width.
         * @return The image width.
         */
        int
        Width() const
        {
            return _width;
        }

        /**
         * Get the image height.
         * @return The image height.
         */
        int
        Height() const
        {
            return _height;
        }

        /**
         * Set the image scaling mode.
         * @param linear If true, set the scaling mode to linear, else, set it to nearest.
         * @return A reference to the image.
         */
        Image&
        Linear(bool linear = true)
        {
            Bind();
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , linear ? GL_LINEAR : GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , linear ? GL_LINEAR : GL_NEAREST);
            return *this;
        }

        /**
         * Load an image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */
        Image&          LoadFile(const std::string path, bool resource = true);

        /**
         * Load an image from a file.
         * @param path The file path.
         * @param resource If true, prepend resourcePath() to the path.
         * @return A reference to an image.
         */
        static Image    FromFile(const std::string path, bool resource = true);

        /**
         * Destructor
         */
        ~Image();
    private:
        void            Gen(SDL_Surface* surface);
        int             _width;
        int             _height;
        GLuint          _texture;
    };
}

#endif