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

#include <cstdint>
#include <LumsInclude/Skeleton/SkeletonAnimation.hpp>

using namespace lm;

void
SkeletonAnimation::loadFromFile(std::ifstream& file)
{
    uint32_t boneCount;

    file.read((char*)&boneCount, 4);
    bones.resize(boneCount);
    for (auto& b : bones)
        b.loadFromFile(file);
}
