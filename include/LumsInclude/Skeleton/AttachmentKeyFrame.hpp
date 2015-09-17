/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    AttachmentKeyFrame.hpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_ATTACHMENT_KEYFRAME_HPP
#define LUMS_SKELETON_ATTACHMENT_KEYFRAME_HPP

#include <LumsInclude/Skeleton/KeyFrame.hpp>

namespace lm
{
    struct AttachmentKeyFrame : public KeyFrame
    {
        void        loadFromFile(std::ifstream& file);

        int         attachment;
    };
}

#endif

