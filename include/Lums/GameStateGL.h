/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GameStateGL.h                                &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAMESTATE_GL_H
#define LUMS_GAMESTATE_GL_H

#include <Lums/GameState.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <Lums/GL.h>
#include <Lums/Angle.h>

namespace lm
{
    class CoreGL;
    
    class GameStateGL : public GameState<GameStateGL, CoreGL>
    {

    };
}

#endif