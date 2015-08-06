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

#ifndef LUMS_SKELETON_BONE_ANIMATION_HPP
#define LUMS_SKELETON_BONE_ANIMATION_HPP

#include <vector>
#include <LumsInclude/Skeleton/RotationKeyFrame.hpp>
#include <LumsInclude/Skeleton/TranslationKeyFrame.hpp>
#include <LumsInclude/Skeleton/IkKeyFrame.hpp>

namespace lm
{
    struct BoneAnimation
    {
        void        loadFromFile(std::ifstream& file);

        bool        hasIk() const { return !iks.empty(); }        

        float       interpolateRotation(int frame) const;
        Vector2f    interpolateTranslation(int frame) const;
        bool        interpolateIk(int frame) const;


        int                                 bone;
        std::vector<RotationKeyFrame>       rotations;
        std::vector<TranslationKeyFrame>    translations;
        std::vector<IkKeyFrame>             iks;
    };
}

#endif

