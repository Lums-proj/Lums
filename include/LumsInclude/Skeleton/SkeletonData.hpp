/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonData.hpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_DATA_HPP
#define LUMS_SKELETON_DATA_HPP

#include <fstream>
#include <unordered_map>
#include <LumsInclude/Skeleton/SkeletonPose.hpp>
#include <LumsInclude/Skeleton/SkeletonAnimation.hpp>

namespace lm
{
    struct SkeletonData
    {
        void    loadFromFile(std::ifstream& file);

        SkeletonPose                                    pose;
        std::unordered_map<size_t, SkeletonAnimation>   animations;
    };
}

#endif
