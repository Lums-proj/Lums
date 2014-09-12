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

namespace lm
{
    class CoreGL;
    
    class GameStateGL : public GameState<GameStateGL, CoreGL>
    {

    };
}

#endif