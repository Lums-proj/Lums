#include "Game.h"
#include <iostream>

void    Game::Load()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, Core().Width(), Core().Height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    _map.Spawn(_player);
}

void    Game::Render()
{
    _map.Render();
    _player.Render();
}

void    Game::Update()
{
    _player.Update();
    _map.ResolveCollision(_player);
}

void    Game::HandleEvent(SDL_Event& event)
{
    bool    b;

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        b = event.type == SDL_KEYDOWN;
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                Core().Stop();
                break;
            case SDLK_LEFT:
                _player.Left(b);
                break;
            case SDLK_RIGHT:
                _player.Right(b);
                break;
        }
    }
}