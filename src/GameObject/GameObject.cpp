/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameObject.cpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/GameObject/GameObject.hpp>

using namespace lm;

GameObject::GameObject()
: position(0.f)
, rotation(0.f)
, scale(1.f)
{

}

Component*
GameObject::attach(size_t id)
{
    Component* c = ComponentFactory::instance().create(id);
    _components.push_back(c);
    return c;
}

void
GameObject::detach(size_t id)
{
    for (int i  = 0; i < _components.size(); ++i)
    {
        if (_components[i]->id() == id)
        {
            delete _components[i];
            _components.erase(_components.begin() + i);
            return;
        }
    }
}

void
GameObject::init()
{
    for (auto& c : _components)
        c->init(*this);
}

void
GameObject::update()
{
    for (auto* c : _components)
        c->update(*this);
}

GameObject::~GameObject()
{
    for (auto c : _components)
        delete c;
}