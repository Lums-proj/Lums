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

#include <vector>

namespace lm
{
    struct SkeletonAnimation
    {
        std::vector<BoneAnimation>  bones;
    };
}

#endif
