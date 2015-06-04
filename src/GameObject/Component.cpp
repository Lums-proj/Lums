/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Component.cpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/GameObject/Component.hpp>
#include <unordered_map>

using namespace lm;

static std::unordered_map<size_t, std::unordered_map<int, Component::method>> bindings;

Component::Component()
{

}

void
Component::bind(int slot, Component::method function) const
{
	bindings[classId()][slot] = function;
}

Component::method
Component::handle(int slot) const
{
	return bindings[classId()][slot];
}

bool
Component::respondTo(int slot) const
{
	return handle(slot);
}

Component::~Component()
{

}
