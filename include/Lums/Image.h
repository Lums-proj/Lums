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
    class Image
    {
    public:
        Image();
        Image(const Image&);
        Image(Image&&);
        Image&          operator=(const Image&);
        Image&          operator=(Image&&);
        void            LoadFile(const std::string path, bool resource = true);
        static Image    FromFile(const std::string path);
        ~Image();
    private:
        int             _width;
        int             _height;
        SDL_Surface*    _image;
        GLuint          _texture;
    };
}

#endif