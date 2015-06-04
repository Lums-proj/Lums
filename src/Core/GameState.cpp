/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameState.cpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Core/GameState.hpp>
#include <LumsInclude/Core/Core.hpp>

using namespace lm;

GameState::GameState()
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
    Core::instance().remove(this);
}

GameState::~GameState()
{
    
}