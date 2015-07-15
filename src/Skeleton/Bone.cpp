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
#include <LumsInclude/Skeleton/Skeleton.hpp>
#include <iostream>

using namespace lm;

Bone::Bone(int parent)
: _parent(parent)
{

}

void
Bone::updateWorldTransform(const Skeleton& skeleton)
{
    if (_parent != -1)
    {
        const Bone& parent = skeleton.bones()[_parent];
        _worldPosition = parent._worldRotMatrix * _position + parent._worldPosition;
        _worldRotation = _inheritRotation ? (parent._worldRotation + _rotation) : _rotation;
    }
    else
    {
        _worldPosition = _position;
        _worldRotation = _rotation;
    }
    _worldRotMatrix = lm::Matrix2f::identity();
    rotate(_worldRotMatrix, _worldRotation);
}

Bone::~Bone()
{

}
