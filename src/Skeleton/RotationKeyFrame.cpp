/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    RotationKeyFrame.cpp                           oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/RotationKeyFrame.hpp>

using namespace lm;

void
RotationKeyFrame::loadFromFile(std::ifstream& file)
{
    KeyFrame::loadFromFile(file);
    file.read((char*)&rotation, 4);
    curve.loadFromFile(file);
}
