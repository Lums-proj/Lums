/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SlotAnimation.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/SlotAnimation.hpp>

using namespace lm;

void
SlotAnimation::loadFromFile(std::ifstream& file)
{
    file.read((char*)&slot, 4);

    uint32_t attachmentCount;
    file.read((char*)&attachmentCount, 4);
    attachments.resize(attachmentCount);
    for (auto& attachment : attachments)
        attachment.loadFromFile(file);
}
