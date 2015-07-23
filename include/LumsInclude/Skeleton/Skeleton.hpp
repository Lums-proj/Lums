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
        void    setAnimation(const char* animation);
        void    transformBone(Matrix4f& matrix, int bone) const;
        void    transformSkin(Matrix4f& matrix, int skin) const;
        void    update();
        void    applyIk(int target, int bone);
        void    applyIk(int target, int parent, int child, float duration);
        size_t  event() const { return _event; }

    private:
        const SkeletonData*             _data;
        int                             _frame;
        const SkeletonAnimation*        _animation;
        size_t                          _event;
    };
}

#endif
