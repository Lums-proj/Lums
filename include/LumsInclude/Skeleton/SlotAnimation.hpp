/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SlotAnimation.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_SLOT_ANIMATION_HPP
#define LUMS_SKELETON_SLOT_ANIMATION_HPP

#include <vector>
#include <fstream>
#include <LumsInclude/Skeleton/AttachmentKeyFrame.hpp>
#include <LumsInclude/Skeleton/Slot.hpp>

namespace lm
{
    struct SkeletonPose;
    struct SlotAnimation
    {
        void        loadFromFile(std::ifstream& file);
        void        animateSlot(SkeletonPose& pose, Slot& slot, int frame) const;

        int                                 slot;
        std::vector<AttachmentKeyFrame>     attachments;
    };
}

#endif

