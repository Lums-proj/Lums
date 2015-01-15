#include "Game.h"
#include <iostream>

Game::Game(lm::Core* core) : lm::GameState(core)
{
    
}

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

void    Game::HandleEvent(const lm::Event& event)
{
    bool    b;

    if (event.type == lm::Event::Type::KeyDown
        || event.type == lm::Event::Type::KeyUp)
    {
        b = event.type == lm::Event::Type::KeyDown;
        switch (event.key)
        {
            case lm::Key::Escape:
                Core().Stop();
                break;
            case lm::Key::Left:
                _player.Left(b);
                break;
            case lm::Key::Right:
                _player.Right(b);
                break;
            default:
                break;
        }
    }
}