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
#include <LumsInclude/Skeleton/SkeletonPose.hpp>

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

void
SlotAnimation::animateSlot(SkeletonPose& pose, Slot& slot, int frame) const
{
    if (attachments.empty())
        return;
    int kf = KeyFrame::lookup(attachments, frame);
    if (kf == -1)
        kf = attachments.size() - 1;
    int att = attachments[kf].attachment;
    slot.attachment = att;
}