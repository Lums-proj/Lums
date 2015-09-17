/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    AttachmentKeyFrame.cpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/AttachmentKeyFrame.hpp>

using namespace lm;

void
AttachmentKeyFrame::loadFromFile(std::ifstream& file)
{
    KeyFrame::loadFromFile(file);
    file.read((char*)&attachment, 4);
}
