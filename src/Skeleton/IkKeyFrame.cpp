/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    IkKeyFrame.cpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/IkKeyFrame.hpp>

using namespace lm;

void
IkKeyFrame::loadFromFile(std::ifstream& file)
{
    KeyFrame::loadFromFile(file);
    char bp;
    file.read(&bp, 1);
    bendPositive = bp;
}
