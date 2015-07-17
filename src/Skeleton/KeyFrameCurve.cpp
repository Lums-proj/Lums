/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    KeyFrameCurve.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/KeyFrameCurve.hpp>

using namespace lm;

void
KeyFrameCurve::loadFromFile(std::ifstream& file)
{
    file.read((char*)&type, 1);
    if (type == Type::Bezier)
    {
        file.read((char*)&c0.x, 4);
        file.read((char*)&c0.y, 4);
        file.read((char*)&c1.x, 4);
        file.read((char*)&c1.y, 4);
    }
}
