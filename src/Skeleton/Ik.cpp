/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Ik.cpp                                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Ik.hpp>

using namespace lm;

void
Ik::loadFromFile(std::ifstream& file)
{
    char positive;

    file.read((char*)bones, 8);
    file.read((char*)&target, 4);
    file.read(&positive, 1);
    bendPositive = positive;
}
