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
#include <LumsInclude/Skeleton/RotationKeyFrame.hpp>
#include <LumsInclude/Skeleton/TranslationKeyFrame.hpp>

namespace lm
{
    struct BoneAnimation
    {
        void        loadFromFile(std::ifstream& file);
        float       interpolateRotation(int frame) const;
        Vector2f    interpolateTranslation(int frame) const;

        int                                 bone;
        std::vector<RotationKeyFrame>       rotations;
        std::vector<TranslationKeyFrame>    translations;
    };
}

#endif

