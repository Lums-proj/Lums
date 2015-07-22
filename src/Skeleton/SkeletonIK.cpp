/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonIK.cpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/SkeletonIK.hpp>

using namespace lm;

void
SkeletonIK::loadFromFile(std::ifstream& file)
{
    char positive;

    file.read((char*)&target, 4);
    file.read((char*)bones, 8);
    file.read(&positive, 1);
    bendPositive = positive;
}
