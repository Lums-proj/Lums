/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonData.cpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <LumsInclude/Skeleton/SkeletonData.hpp>

using namespace lm;

void
SkeletonData::loadFromFile(std::ifstream& file)
{   
    pose.loadFromFile(file);

    uint32_t animCount;
    char* animName;
    int animLen;

    file.read((char*)&animCount, 4);
    for (int i = 0; i < animCount; ++i)
    {
        file.read((char*)&animLen, 4);
        animName = new char[animLen + 1];
        animName[animLen] = 0;
        file.read(animName, animLen);
        size_t key = lm::sym(animName);
        animations[key].loadFromFile(file);
    }
}
