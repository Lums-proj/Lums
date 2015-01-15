#include "Game.h"
#include <iostream>

Game::Game(lm::Core* core) : lm::GameState(core)
{
    
}

void    Game::load()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, Core().width(), Core().height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    _map.Spawn(_player);
}

void    Game::render()
{
    _map.Render();
    _player.Render();
}

void    Game::update()
{
    _player.Update();
    _map.ResolveCollision(_player);
}

void    Game::handleEvent(const lm::Event& event)
{
    bool    b;

    if (event.type == lm::Event::Type::KeyDown
        || event.type == lm::Event::Type::KeyUp)
    {
        b = event.type == lm::Event::Type::KeyDown;
        switch (event.key)
        {
            case lm::Key::Escape:
                Core().stop();
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