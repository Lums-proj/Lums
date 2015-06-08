#include "Game.hpp"

Game::Game()
{

}

void
Game::load()
{

}

void
Game::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown)
    {
        if (event.key == lm::Key::Escape)
            lm::Core::instance().stop();
    }
}

void
Game::update()
{

}

void
Game::render()
{

}

void
Game::unload()
{

}

Game::~Game()
{

}
