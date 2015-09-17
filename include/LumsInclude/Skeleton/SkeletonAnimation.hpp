/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonAnimation.hpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_ANIMATION_HPP
#define LUMS_SKELETON_ANIMATION_HPP

#include <fstream>
#include <vector>
#include <LumsInclude/Skeleton/BoneAnimation.hpp>
#include <LumsInclude/Skeleton/IkAnimation.hpp>
#include <LumsInclude/Skeleton/EventKeyFrame.hpp>
#include <LumsInclude/Skeleton/SlotAnimation.hpp>

namespace lm
{
    struct SkeletonAnimation
    {
        void    loadFromFile(std::ifstream& file);
        void    computeLength();
        //size_t  getEvent(int frame) const;

        std::vector<BoneAnimation>  bones;
        std::vector<IkAnimation>    iks;
        std::vector<EventKeyFrame>  events;
        std::vector<SlotAnimation>  slots;
        int                         length;
    };
}

#endif
