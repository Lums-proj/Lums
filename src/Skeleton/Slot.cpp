/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Slot.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Slot.hpp>

using namespace lm;

void
Slot::loadFromFile(std::ifstream& file)
{
    file.read((char*)&bone, 4);
    file.read((char*)&attachment, 4);
}
