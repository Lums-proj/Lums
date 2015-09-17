/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    EventKeyFrame.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/EventKeyFrame.hpp>

using namespace lm;

void
EventKeyFrame::loadFromFile(std::ifstream& file)
{
    uint32_t nameLen;
    char* name;

    KeyFrame::loadFromFile(file);
    file.read((char*)&nameLen, 4);
    name = new char[nameLen + 1];
    name[nameLen] = 0;
    file.read(name, nameLen);
    event = lm::sym(name);
    delete [] name;
}
