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
#include <LumsInclude/Skeleton/SkeletonPose.hpp>

using namespace lm;

Skin::Skin(int bone, int texture)
: _bone(bone)
, _texture(texture)
{

}

void
Skin::transform(Matrix4f& matrix) const
{
    rotate(matrix, _worldRotation, {0, 0, 1});
    translate(matrix, {_worldPosition.x, _worldPosition.y, 0});
}

void
Skin::updateWorldTransform(const SkeletonPose& skeleton)
{
    const Bone& parent = skeleton.bones()[_bone];
    _worldPosition = parent._worldRotMatrix * _position + parent._worldPosition;
    _worldRotation = parent._worldRotation + _rotation;
}

Skin::~Skin()
{

}
