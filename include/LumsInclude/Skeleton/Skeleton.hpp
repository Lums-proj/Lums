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

#include <LumsInclude/Skeleton/Bone.hpp>

namespace lm
{
    class Skeleton
    {
    public:
        void    load(const std::string& path, bool resource = true);
        void    loadBinary(const BObject& object);

    private:
        std::vector<Bone>       _bones;
    };
}

#endif
