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
{

}

void
GameObject::addComponent(Component* component)
{
	_components.push_back(std::unique_ptr<Component>(component));
}

GameObject::~GameObject()
{

}
