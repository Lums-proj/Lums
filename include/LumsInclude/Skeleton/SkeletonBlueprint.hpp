/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonBlueprint.hpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_BLUEPRINT_HPP
#define LUMS_SKELETON_BLUEPRINT_HPP

#include <LumsInclude/Provider.hpp>
#include <LumsInclude/Binary/BObject.hpp>
#include <LumsInclude/Skeleton/SkeletonData.hpp>

namespace lm
{
    class SkeletonBlueprint
    {
    public:
        SkeletonBlueprint();
        void    loadBinary(const BObject& object);
        ~SkeletonBlueprint();

    private:
        SkeletonData    _data;
    };

    using SkeletonProvider = Provider<SkeletonBlueprint>;
}

#endif
