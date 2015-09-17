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

#ifndef LUMS_SKELETON_EVENT_KEYFRAME_HPP
#define LUMS_SKELETON_EVENT_KEYFRAME_HPP

#include <LumsInclude/Skeleton/KeyFrame.hpp>

namespace lm
{
    struct EventKeyFrame : public KeyFrame
    {
        void        loadFromFile(std::ifstream& file);

        size_t      event;
    };
}

#endif

