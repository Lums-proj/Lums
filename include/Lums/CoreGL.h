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
#include <SDL2/SDL_opengl.h>

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
        typedef SDL_Event&  Event;
        typedef GameStateGL State;
    };
    
    class CoreGL : public Core<CoreGL>
    {
    public:
        /**
         *
         */
        CoreGL(int w, int h, const char* name = "", bool fullscreen = false);

        int     Width()
        {
            return _width;
        }

        int     Height()
        {
            return _height;
        }

        /**
         * Poll an event from the event stream.
         * Already called by the main loop.
         * @return True if an event exist.
         */
        bool    PollEvent()
        {
            return SDL_PollEvent(&_event) != 0;
        }
        
        void    ClearScreen()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
        }
        
        void    RefreshScreen()
        {
            SDL_GL_SwapWindow(_win);
        }
        
        ~CoreGL();
        
    private:
        int                 _width;
        int                 _height;
        SDL_Window*         _win;
        SDL_GLContext       _glcontext;
    };
}

#endif