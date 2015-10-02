/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Transformable.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Transformable.hpp>

using namespace lm;

void
Transformable::loadFromFile(std::ifstream& file)
{
    file.read((char*)&position.x, 4);
    file.read((char*)&position.y, 4);
    file.read((char*)&scale.x, 4);
    file.read((char*)&scale.y, 4);
    file.read((char*)&rotation, 4);
}

void
Transformable::update(SkeletonPose& skeleton)
{
    Transformable* p = parent(skeleton);
    if (p)
    {
        worldPosition = p->matrix * position + p->worldPosition;
        worldRotation = (doesInheritRotation() ? p->worldRotation : 0.f) + rotation;
        worldScale.x = scale.x * p->worldScale.x;
        worldScale.y = scale.y * p->worldScale.y;
    }
    else
    {
        worldPosition = position;
        worldRotation = rotation;
        worldScale = scale;
    }
    matrix = Matrix2f::identity();
    rotate(matrix, worldRotation);
   // scale(_worldRotMatrix, _worldScale.x, _worldScale.y);
}

void
Transformable::transform(Matrix4f& mat) const
{
    rotate(mat, worldRotation, {0, 0, 1});
    translate(mat, {worldPosition.x, worldPosition.y, 0});
}

void
Transformable::worldToLocal(Vector2f& world) const
{
    const Matrix2f& wr = matrix;
    Vector2f diff = world - worldPosition;

    float invDet = 1.f / (wr[0][0] * wr[1][1] - wr[0][1] * wr[1][0]);
    world.x = diff.x * wr[0][0] * invDet - diff.y * wr[1][0] * invDet;
    world.y = diff.y * wr[1][1] * invDet - diff.x * wr[0][1] * invDet;
}
