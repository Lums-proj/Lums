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
#include <string>

namespace lm
{
    class Image
    {
    public:
        Image();
        void    LoadFile(const std::string path, bool resource = true);
        
        ~Image();
    private:
        unsigned int    _width;
        unsigned int    _height;
        unsigned int    _mem_width;
        unsigned int    _mem_height;
        SDL_Surface*    _image;
    };
}

#endif