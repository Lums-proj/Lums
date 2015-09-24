/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonPose.hpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_POSE_HPP
#define LUMS_SKELETON_POSE_HPP

#include <fstream>
#include <vector>
#include <unordered_map>
#include <LumsInclude/Skeleton/Bone.hpp>
#include <LumsInclude/Skeleton/Slot.hpp>
#include <LumsInclude/Skeleton/Attachment.hpp>
#include <LumsInclude/Skeleton/Ik.hpp>


namespace lm
{
    struct SkeletonPose
    {
        void        loadFromFile(std::ifstream& file);
        void        update();

        const Bone& getBone(const char* name) const { return getBone(lm::sym(name)); }
        const Bone& getBone(size_t boneId) const { return bones[boneMap.at(boneId)]; }
        
        std::vector<Bone>               bones;
        std::vector<Slot>               slots;
        std::vector<Attachment>         attachments;
        std::vector<Ik>                 iks;

        std::unordered_map<size_t, int> boneMap;
    };
}

#endif
