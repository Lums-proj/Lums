 /* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    IkAnimation.cpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/IkAnimation.hpp>

using namespace lm;

void
IkAnimation::loadFromFile(std::ifstream& file)
{
    file.read((char*)&ik, 4);

    uint32_t ikCount;
    file.read((char*)&ikCount, 4);
    iks.resize(ikCount);
    for (auto& i : iks)
        i.loadFromFile(file);
}
