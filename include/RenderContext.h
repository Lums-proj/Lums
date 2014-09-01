/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    RenderContext.h                              &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_RENDERCONTEXT_H
#define LUMS_RENDERCONTEXT_H

#include <SDL2/SDL.h>

namespace lm
{
    /**
     * A POD class representing a render context.
     * All members are public.
     */
    struct RenderContext
    {
        SDL_Window*		window;
        SDL_Renderer*	renderer;
        int				w;
        int				h;
    };
}

#endif