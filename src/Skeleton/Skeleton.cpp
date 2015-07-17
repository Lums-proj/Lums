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
{

}

Skeleton::Skeleton(const SkeletonData& data)
: _data(&data)
{
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
    _frame = -1;
    _animation = &(_data->animations.at(sym(animation)));
    update();
}

void
Skeleton::transformBone(Matrix4f& matrix, int bone) const
{
    Matrix4f m = Matrix4f::identity();
    _bones[bone].transform(m);
    //_data->pose.bones()[bone].transform(m);
    matrix *= m;
}

void
Skeleton::transformSkin(Matrix4f& matrix, int skin) const
{
    Matrix4f m = Matrix4f::identity();
    _skins[skin].transform(m);
    //_data->pose.skins()[skin].transform(m);
    matrix *= m;
}

void
Skeleton::update()
{
    const auto& bones = _animation->bones;
    const unsigned max = bones.size();
    _frame++;
    for (int i = 0; i < max; ++i)
    {
        int bone = bones[i].bone;
        std::cout << "bone: " << bone << std::endl;
        std::cout << "from: " << i << std::endl;
        float rotation = bones[i].interpolateRotation(_frame);
        Vector2f translation = bones[i].interpolateTranslation(_frame);
        _bones[bone].setRotation(_data->pose.bones()[bone].rotation() + rotation);
        _bones[bone].setPosition(_data->pose.bones()[bone].position() + translation);
    }
    SkeletonPose::update();
}
