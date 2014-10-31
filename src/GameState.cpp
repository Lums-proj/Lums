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
GameState::Load()
{
    
}

void
GameState::Unload()
{
    
}

void
GameState::Reload()
{
    Unload();
    Load();
}

void
GameState::Remove()
{
    _core->Remove(this);
}

GameState::~GameState()
{
    
}