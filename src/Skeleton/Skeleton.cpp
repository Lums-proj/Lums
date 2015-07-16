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

Skeleton::Skeleton(const SkeletonData& data)
: _data(&data)
{
    *this = data.pose;
    setToPose();
}

void
Skeleton::setToPose()
{
    for (auto& b : bones())
    {
        b.setRotation(0.f);
        b.setPosition({0.f, 0.f});
    }
    for (auto& s : skins())
    {
        s.setRotation(0.f);
        s.setPosition({0.f, 0.f});
    }
    SkeletonPose::update();
}