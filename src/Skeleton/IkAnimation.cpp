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

bool
IkAnimation::getBendPositive(bool def, int frame) const
{
    if (iks.empty())
        return def;
    int keyFrame = KeyFrame::lookup(iks, frame);
    if (keyFrame == -1)
        return iks.back().bendPositive;
    return iks[keyFrame].bendPositive;
}