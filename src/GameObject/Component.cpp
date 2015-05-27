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

static std::unordered_map<std::pair<size_t, int>, void*> bindings;

Component::Component()
{

}

void
Component::bind(int slot, void* function) const
{
	bindings[std::make_pair(classId(), slot)] = function;
}

void*
Component::handle(int slot) const
{
	return bindings[std::make_pair(classId(), slot)];
}

bool
Component::respondTo(int slot) const
{
	return handle(slot);
}

Component::~Component()
{

}
