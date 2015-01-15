/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GameState.cpp                                &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/GameState.h>
#include <Lums/Core.h>

using namespace lm;

GameState::GameState(lm::Core* core)
: _core(core)
{
    
}

void
GameState::load()
{
    
}

void
GameState::unload()
{
    
}

void
GameState::reload()
{
    unload();
    load();
}

void
GameState::remove()
{
    _core->remove(this);
}

GameState::~GameState()
{
    
}