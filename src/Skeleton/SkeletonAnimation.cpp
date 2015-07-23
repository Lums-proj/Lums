/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonAnimation.cpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdint>
#include <LumsInclude/Skeleton/SkeletonAnimation.hpp>

using namespace lm;

void
SkeletonAnimation::loadFromFile(std::ifstream& file)
{
    uint32_t boneCount;
    uint32_t eventCount;

    file.read((char*)&boneCount, 4);
    bones.resize(boneCount);
    for (auto& b : bones)
        b.loadFromFile(file);
    file.read((char*)&eventCount, 4);
    events.resize(eventCount);
    for (auto& e : events)
        e.loadFromFile(file);
}

size_t
SkeletonAnimation::getEvent(int frame) const
{
    for (auto& e : events)
    {
        if (e.frame == frame)
            return e.name;
    }
    return 0;
}
