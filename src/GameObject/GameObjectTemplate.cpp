/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameObjectTemplate.cpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/GameObject/GameObjectTemplate.hpp>
#include <LumsInclude/Binary/BObject.hpp>
#include <LumsInclude/Binary/BArray.hpp>

using namespace lm;

GameObjectTemplate::GameObjectTemplate()
{

}

void
GameObjectTemplate::load()
{

}

void
GameObjectTemplate::loadBinary(const BObject& object)
{
    auto& components = object["components"].asObject();
    for (auto c : components)
        _components[sym(c.first)] = c.second.asObject();
    if (object.hasProperty("tags"))
    {
        auto& tags = object["tags"].asArray();
        for (unsigned i = 0; i < tags.size(); ++i)
            _tags.push_back(sym(tags[i].asString()));
    }
}

GameObject*
GameObjectTemplate::operator()()
{
    GameObject* go = new GameObject;
    for (auto& o : _components)
    {
        Component* c = go->attach(o.first);
        c->loadBinary(o.second);
    }
    for (auto t : _tags)
        go->setTag(t);
    go->init();
    return go;
}

GameObjectTemplate::~GameObjectTemplate()
{

}
