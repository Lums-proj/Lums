/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skeleton.cpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Skeleton.hpp>
#include <iostream>

using namespace lm;

Skeleton::Skeleton()
: _data(nullptr)
, _frame(0)
, _animation(nullptr)
, _flipX(false)
{

}

Skeleton::Skeleton(const SkeletonData& data)
: Skeleton()
{
    _data = &data;
    _bones = data.pose.bones();
    _skins = data.pose.skins();
    //setToPose();
}

void
Skeleton::setToPose()
{
    for (auto& b : _bones)
    {
        b.setRotation(0.f);
        b.setPosition({0.f, 0.f});
    }
    for (auto& s : _skins)
    {
        s.setRotation(0.f);
        s.setPosition({0.f, 0.f});
    }
    SkeletonPose::update();
}

void
Skeleton::setAnimation(const char* animation)
{
    _finished = false;
    _frame = -1;
    _animation = &(_data->animations.at(sym(animation)));
    update();
}

void
Skeleton::transformBone(Matrix4f& matrix, int bone) const
{
    Matrix4f m = Matrix4f::identity();
    _bones[bone].transform(m);
    matrix *= m;
    if (_flipX)
    {
        m = Matrix4f::identity();
        m[0][0] = -1.f;
        matrix *= m;
    }
}

void
Skeleton::transformSkin(Matrix4f& matrix, int skin) const
{
    Matrix4f m = Matrix4f::identity();
    _skins[skin].transform(m);
    matrix *= m;
    if (_flipX)
    {
        m = Matrix4f::identity();
        m[0][0] = -1.f;
        matrix *= m;
    }
}

void
Skeleton::update()
{
    const auto& bones = _animation->bones;
    const unsigned max = bones.size();

    if (_finished)
        return;

    _frame++;
    for (int i = 0; i < max; ++i)
    {
        int bone = bones[i].bone;
        float rotation = bones[i].interpolateRotation(_frame);
        Vector2f translation = bones[i].interpolateTranslation(_frame);
        _bones[bone].setRotation(_data->pose.bones()[bone].rotation() + rotation);
        _bones[bone].setPosition(_data->pose.bones()[bone].position() + translation);
    }
    SkeletonPose::update();
    for (auto& ik : _data->iks)
    {
        if (ik.bones[1] == -1)
            applyIk(ik.target, ik.bones[0]);
        else
            applyIk(ik.target, ik.bones[0], ik.bones[1], (ik.bendPositive ? 1.f : -1.f));
    }
    SkeletonPose::update();
    _event = _animation->getEvent(_frame);
    if (_frame == _animation->length)
        _finished = true;
}

void
Skeleton::applyIk(int target, int bone)
{
    const Bone& b = _bones[bone];
    lm::Vector2f tPos = _bones[target].worldPosition();
    lm::Vector2f bPos = b.worldPosition();
    lm::Vector2f diff = tPos - bPos;
    float rotation = atan2f(diff.y, diff.x) * (180.f / M_PI);
    float parentRotation = b.inheritRotation() ? _bones[b.parent()].rotation() : 0;
    _bones[bone].setRotation(rotation - parentRotation);
}

void
Skeleton::applyIk(int target, int parent, int child, float direction)
{
    Bone& parentBone = _bones[parent];
    Bone& childBone = _bones[child];
    Bone& targetBone = _bones[target];
    
    Vector2f tmp;
    Vector2f targetPos = targetBone.worldPosition();
    Vector2f parentPos = parentBone.position();
    Vector2f childPos = childBone.position();

    int parentParent = parentBone.parent();

    if (parentParent != -1)
    {
        tmp = targetPos;
        _bones[parentParent].worldToLocal(tmp);
        targetPos = tmp - parentPos;
    }
    else
        targetPos -= parentPos;

    float offset = atan2f(childPos.y, childPos.x);
    float len1 = length(childPos);
    float len2 = childBone.length();
    float cosDenom = 2.f * len1 * len2;

    if (cosDenom < 0.0001f)
    {
        childBone.setRotation(childBone.rotation() + (atan2f(targetPos.y, targetPos.x) * (180.f / M_PI) - parentBone.rotation() - childBone.rotation()));
        return;
    }

    float cosValue = (targetPos.x * targetPos.x + targetPos.y * targetPos.y - len1 * len1 - len2 * len2) / cosDenom;
    
    if (cosValue < -1)
        cosValue = -1;
    else if (cosValue > 1)
        cosValue = 1;

    float childAngle = acosf(cosValue) * direction;

    float adjacent = len1 + len2 * cosValue;
    float opposite = len2 * sinf(childAngle);
    float parentAngle = atan2f(targetPos.y * adjacent - targetPos.x * opposite, targetPos.x * adjacent + targetPos.y * opposite);
    float rotation = (parentAngle - offset) * (180.f / M_PI) - parentBone.rotation();

    while (rotation > 180.f)
        rotation -= 360.f;
    while (rotation <= -180.f)
        rotation += 360.f;

    parentBone.setRotation(parentBone.rotation() + rotation);
    rotation = (childAngle - offset) * (180.f / M_PI) - childBone.rotation();
    while (rotation > 180.f)
        rotation -= 360.f;
    while (rotation <= -180.f)
        rotation += 360.f;
    childBone.setRotation(childBone.rotation() + rotation);
}
