/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skin.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Skin.hpp>
#include <LumsInclude/Skeleton/Skeleton.hpp>

using namespace lm;

Skin::Skin(int bone, int texture)
: _bone(bone)
, _texture(texture)
{

}

void
Skin::updateWorldTransform(const Skeleton& skeleton)
{
    const Bone& parent = skeleton.bones()[_bone];
    _worldPosition = parent._worldRotMatrix * _position + parent._worldPosition;
    _worldRotation = parent._worldRotation + _rotation;
}

Skin::~Skin()
{

}
