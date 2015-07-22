/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonEvent.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Common.hpp>
#include <LumsInclude/Skeleton/SkeletonEvent.hpp>

using namespace lm;

void
SkeletonEvent::loadFromFile(std::ifstream& file)
{
    uint32_t nameLen;
    file.read((char*)&nameLen, 4);
    char* tmp = new char[nameLen + 1];
    tmp[nameLen] = 0;

    file.read(tmp, nameLen);
    name = sym(tmp);
    file.read((char*)&frame, 4);

    delete [] tmp;
}