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
#include <iostream>
#include <LumsInclude/Skeleton/SkeletonData.hpp>

using namespace lm;

void
SkeletonData::loadFromFile(std::ifstream& file)
{
    pose.loadFromFile(file);
    uint32_t ikCount;
    uint32_t animCount;
    file.read((char*)&ikCount, 4);
    iks.resize(ikCount);
    for (auto& ik : iks)
        ik.loadFromFile(file);
    file.read((char*)&animCount, 4);
    for (unsigned i = 0; i < animCount; ++i)
    {
        char* name;
        uint32_t nameLen;
        file.read((char*)&nameLen, 4);
        name = new char[nameLen + 1];
        name[nameLen] = 0;
        file.read(name, nameLen);
        animations[sym(name)].loadFromFile(file);
        std::cout << i << std::endl;
        std::cout << name << std::endl;
        delete [] name;
    }
}
