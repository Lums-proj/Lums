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

using namespace lm;

Skeleton::Skeleton()
: _data(nullptr)
{

}

Skeleton::Skeleton(const SkeletonData& data)
: _data(&data)
{
    _bones = data.pose.bones();
    _skins = data.pose.skins();
    setToPose();
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
Skeleton::transformBone(Matrix4f& matrix, int bone) const
{
    Matrix4f m = Matrix4f::identity();
    _bones[bone].transform(m);
    _data->pose.bones()[bone].transform(m);
    matrix *= m;
}

void
Skeleton::transformSkin(Matrix4f& matrix, int skin) const
{
    Matrix4f m = Matrix4f::identity();
    _skins[skin].transform(m);
    _data->pose.skins()[skin].transform(m);
    matrix *= m;
}
