/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    TranslationKeyFrame.cpp                        oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/TranslationKeyFrame.hpp>

using namespace lm;

void
TranslationKeyFrame::loadFromFile(std::ifstream& file)
{
    KeyFrame::loadFromFile(file);
    file.read((char*)&translation.x, 4);
    file.read((char*)&translation.y, 4);
    curve.loadFromFile(file);
}
