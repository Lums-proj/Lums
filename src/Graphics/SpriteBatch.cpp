/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SpriteBatch.cpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Graphics/SpriteBatch.hpp>

using namespace lm;

void
SpriteBatch::begin()
{
    texture = nullptr;
}

void
SpriteBatch::end()
{
    send();
    render();
    flush();
}

void
SpriteBatch::setTexture(const Texture* texture)
{
    if (this->texture != texture)
    {
        if (this->texture != nullptr)
            end();
        this->texture = texture;
    }
}
