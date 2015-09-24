/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Bone.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_BONE_HPP
#define LUMS_SKELETON_BONE_HPP

#include <LumsInclude/Skeleton/Transformable.hpp>

namespace lm
{
    struct Bone : public Transformable
    {
        void            loadFromFile(std::ifstream& stream);
        Transformable*  parent(SkeletonPose& skeleton) const;
        bool            doesInheritRotation() const { return inheritRotation; }
        
        float   length;
        int     parentBone;
        bool    inheritRotation;
        size_t  name;
    };
}

#endif
