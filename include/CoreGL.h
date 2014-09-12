/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    CoreGL.h                                     &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_CORE_GL_H
#define LUMS_CORE_GL_H

#include <Lums/Core.h>
#include <SDL2/SDL.h>

namespace lm
{
    /**
     * A class representing an OpenGL core.
     */
    class CoreGL;
    class GameStateGL;

    template<>
    struct CoreTraits<CoreGL>
    {
        typedef SDL_Event*  Event;
        typedef GameStateGL State;
    };
    
    class CoreGL : public Core<CoreGL>
    {

    };
}

#endif