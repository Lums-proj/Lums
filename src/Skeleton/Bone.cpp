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

Bone::Bone(int parent)
: _parent(parent)
, _transform(Matrix4f::identity())
{

}

Bone::~Bone()
{

}
