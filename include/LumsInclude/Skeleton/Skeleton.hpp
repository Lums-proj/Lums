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

namespace lm
{
    class Skeleton : public SkeletonPose
    {
    public:
        explicit Skeleton(const SkeletonData& data);

        void    setToPose();

    private:
        const SkeletonData*   _data;
    };
}

#endif
