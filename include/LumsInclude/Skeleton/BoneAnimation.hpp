/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BoneAnimation.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BONE_ANIMATION_HPP
#define LUMS_BONE_ANIMATION_HPP

#include <vector>

namespace lm
{
    struct BoneAnimation
    {
        int                                 bone;
        std::vector<RotationKeyFrame>       rotations;
        std::vector<TranslationKeyFrame>    translations;
    };
}

#endif

