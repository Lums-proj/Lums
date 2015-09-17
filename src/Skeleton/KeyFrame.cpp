/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    KeyFrame.cpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/KeyFrame.hpp>

using namespace lm;

void
KeyFrame::loadFromFile(std::ifstream& file)
{
    file.read((char*)&frame, 4);
}
