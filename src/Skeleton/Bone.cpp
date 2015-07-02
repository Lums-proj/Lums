/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Bone.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Bone.hpp>

using namespace lm;

Bone::Bone(const char* name, Bone* parent)
: Bone(sym(name), parent)
{

}

Bone::Bone(size_t id, Bone* parent)
: _id(id)
, _parent(parent)
{

}

Bone::~Bone()
{

}
