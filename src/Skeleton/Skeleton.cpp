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
#include <LumsInclude/Graphics/Graphics.hpp>
#include <LumsInclude/Math/Math.hpp>

#include <iostream>

using namespace lm;

Skeleton::Skeleton()
: _data(nullptr)
, _frame(0)
, _animation(nullptr)
, _flipX(false)
, _interpolationLength(0)
, _interpolating(false)
, _interpolationAcc(0)
{

}

Skeleton::Skeleton(const SkeletonData& data)
: Skeleton()
{
    _data = &data;
    bones = data.pose.bones;
    iks = data.pose.iks;
    slots = data.pose.slots;
    attachments = data.pose.attachments;
}

void
Skeleton::setToPose()
{
    bones = _data->pose.bones;
    iks = _data->pose.iks;
    slots = _data->pose.slots;
    attachments = _data->pose.attachments;
    SkeletonPose::update();
}

void
Skeleton::setAnimation(const char* animation, bool loop, bool repeat, int interpolation)
{
    setAnimation(sym(animation), loop, repeat, interpolation);
}

void
Skeleton::setAnimation(size_t animation, bool loop, bool repeat, int interpolation)
{
    if (!repeat && animation == _animationHash)
        return;
    if (interpolation && animation != _animationHash)
    {
        _interpolating = true;
        _interpolationAcc = 0;
        _interpolationLength = interpolation;
    }
    else
        _interpolating = false;
    _loop = loop;
    _animationHash = animation;
    _finished = false;
    _frame = 0;
    _animation = &(_data->animations.at(animation));
    update();
}

void
Skeleton::update()
{
    if (_animation)
        updateAnimation();

    /*
    SkeletonPose::update();
    for (auto& ik : _iks)
    {
        bool bendPositive;

        if (bones[ik.target].hasIk())
            bendPositive = bones[ik.target].interpolateIk(_frame);
        else
            bendPositive = ik.bendPositive;
        if (ik.bones[1] == -1)
            applyIk(ik.target, ik.bones[0]);
        else
            applyIk(ik.target, ik.bones[0], ik.bones[1], (bendPositive ? 1.f : -1.f));
    }
    SkeletonPose::update();
    _event = _animation->getEvent(_frame);
    */
    SkeletonPose::update();
}

void
Skeleton::updateAnimation()
{
    const auto& animBones = _animation->bones;

    if (_finished)
        return;

    for (auto& aBone : animBones)
    {
        int boneIndex = aBone.bone;
        Bone& bone = bones[boneIndex];
        float rotation = aBone.getRotation(_frame);
        Vector2f translation = aBone.getTranslation(_frame);
        float newRotation = _data->pose.bones[boneIndex].rotation + rotation;
        Vector2f newTranslation = _data->pose.bones[boneIndex].position + translation;

        if (_interpolating)
        {
            float alpha = 1.f / (_interpolationLength - _interpolationAcc);
            newRotation = interpolateAngle(bone.rotation, newRotation, alpha);
            newTranslation.x = interpolate(bone.position.x, newTranslation.x, alpha);
            newTranslation.y = interpolate(bone.position.y, newTranslation.y, alpha);
        }
        bone.rotation = newRotation;
        bone.position = newTranslation;
        bone.dirty = true;
    }
    SkeletonPose::update();
    for (auto& ik : iks)
    {
        bool bendPositive = true;

        if (ik.bones[1] == -1)
            applyIk(ik.target, ik.bones[0]);
        else
            applyIk(ik.target, ik.bones[0], ik.bones[1], (bendPositive ? 1.f : -1.f));
    }

    if (!_interpolating)
        _frame++;
    else
        _interpolationAcc++;
    if (_interpolationAcc >= _interpolationLength)
        _interpolating = false;
    if (_frame == _animation->length)
    {
        if (!_loop)
            _finished = true;
        else
            _frame = -1;
    }
}

void
Skeleton::applyIk(int target, int bone)
{
    const Bone& b = bones[bone];
    lm::Vector2f tPos = bones[target].worldPosition;
    lm::Vector2f bPos = b.worldPosition;
    lm::Vector2f diff = tPos - bPos;
    float rotation = atan2f(diff.y, diff.x) * (180.f / M_PI);
    float parentRotation = b.inheritRotation ? b.parent(*this)->worldRotation : 0;
    bones[bone].rotation = rotation - parentRotation;
    bones[bone].dirty = true;
}

void
Skeleton::applyIk(int target, int parent, int child, float direction)
{
    Bone& parentBone = bones[parent];
    Bone& childBone = bones[child];
    Bone& targetBone = bones[target];
    
    Vector2f tmp;
    Vector2f targetPos = targetBone.worldPosition;
    Vector2f parentPos = parentBone.position;
    Vector2f childPos = childBone.position;

    Bone* parentParent = static_cast<Bone*>(parentBone.parent(*this));

    if (parentParent)
    {
        tmp = targetPos;
        parentParent->worldToLocal(tmp);
        targetPos = tmp - parentPos;
    }
    else
        targetPos -= parentPos;

    float offset = atan2f(childPos.y, childPos.x);
    float len1 = length(childPos);
    float len2 = childBone.length;
    float cosDenom = 2.f * len1 * len2;

    if (cosDenom < 0.0001f)
    {
        childBone.rotation = childBone.rotation + (atan2f(targetPos.y, targetPos.x) * (180.f / M_PI) - parentBone.rotation - childBone.rotation);
        childBone.dirty = true;
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
    float rotation = (parentAngle - offset) * (180.f / M_PI) - parentBone.rotation;

    while (rotation > 180.f)
        rotation -= 360.f;
    while (rotation <= -180.f)
        rotation += 360.f;

    parentBone.rotation = parentBone.rotation + rotation;
    parentBone.dirty = true;
    rotation = (childAngle - offset) * (180.f / M_PI) - childBone.rotation;
    while (rotation > 180.f)
        rotation -= 360.f;
    while (rotation <= -180.f)
        rotation += 360.f;
    childBone.rotation = childBone.rotation + rotation;
    childBone.dirty = true;
}
