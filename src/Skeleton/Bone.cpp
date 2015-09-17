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
#include <LumsInclude/Skeleton/SkeletonPose.hpp>

using namespace lm;

void
Bone::loadFromFile(std::ifstream& file)
{
    uint32_t nameLen;
    char* name;
    file.read((char*)&nameLen, 4);
    name = new char[nameLen + 1];
    name[nameLen] = 0;
    file.read(name, nameLen);
    delete [] name;

    Transformable::loadFromFile(file);
    file.read((char*)&length, 4);
    file.read((char*)&parentBone, 4);

    char ir;
    file.read((char*)&ir, 1);
    inheritRotation = ir;
}

Transformable*
Bone::parent(SkeletonPose& skeleton) const
{
    if (parentBone != -1)
        return &skeleton.bones[parentBone];
    return nullptr;
}

// #include <LumsInclude/Skeleton/SkeletonPose.hpp>

// using namespace lm;

// Bone::Bone(int parent)
// : _parent(parent)
// {

// }

// void
// Bone::transform(Matrix4f& matrix) const
// {
//     rotate(matrix, _worldRotation, {0, 0, 1});
//     translate(matrix, {_worldPosition.x, _worldPosition.y, 0});
// }

// void
// Bone::worldToLocal(Vector2f& world) const
// {
//     Matrix2f wr = _worldRotMatrix;
//     Vector2f diff = world - _worldPosition;

//     float invDet = 1.f / (wr[0][0] * wr[1][1] - wr[0][1] * wr[1][0]);
//     world.x = diff.x * wr[0][0] * invDet - diff.y * wr[1][0] * invDet;
//     world.y = diff.y * wr[1][1] * invDet - diff.x * wr[0][1] * invDet;
// }

// void
// Bone::updateWorldTransform(const SkeletonPose& skeleton)
// {
//     if (_parent != -1)
//     {
//         const Bone& parent = skeleton.bones()[_parent];
//         _worldPosition = parent._worldRotMatrix * _position + parent._worldPosition;
//         _worldRotation = _inheritRotation ? (parent._worldRotation + _rotation) : _rotation;
//         _worldScale.x = _scale.x * parent._worldScale.x;
//         _worldScale.y = _scale.y * parent._worldScale.y;
//     }
//     else
//     {
//         _worldPosition = _position;
//         _worldRotation = _rotation;
//         _worldScale = _scale;
//     }
//     _worldRotMatrix = lm::Matrix2f::identity();
//     rotate(_worldRotMatrix, _worldRotation);
//     scale(_worldRotMatrix, _worldScale.x, _worldScale.y);
// }

// Bone::~Bone()
// {

// }
