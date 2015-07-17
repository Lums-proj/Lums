/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skeleton.hpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_HPP
#define LUMS_SKELETON_HPP

#include <LumsInclude/Skeleton/SkeletonPose.hpp>
#include <LumsInclude/Skeleton/SkeletonData.hpp>

namespace lm
{
    class Skeleton : public SkeletonPose
    {
    public:
        Skeleton();
        explicit Skeleton(const SkeletonData& data);

        void    setToPose();
        void    transformBone(Matrix4f& matrix, int bone) const;
        void    transformSkin(Matrix4f& matrix, int skin) const;

    private:
        const SkeletonData*   _data;
    };
}

#endif
