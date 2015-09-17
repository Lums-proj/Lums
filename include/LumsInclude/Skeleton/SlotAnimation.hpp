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

namespace lm
{
    struct SlotAnimation
    {
        void        loadFromFile(std::ifstream& file);    

        //int         getAttachment(int frame);

        int                                 slot;
        std::vector<AttachmentKeyFrame>     attachments;
    };
}

#endif

