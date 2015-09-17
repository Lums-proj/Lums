 /* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    IkAnimation.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_IK_ANIMATION_HPP
#define LUMS_SKELETON_IK_ANIMATION_HPP

#include <vector>
#include <LumsInclude/Skeleton/IkKeyFrame.hpp>

namespace lm
{
    struct IkAnimation
    {
        void    loadFromFile(std::ifstream& file);
        bool    getBendPositive(bool def, int frame) const;

        int                                 ik;
        std::vector<IkKeyFrame>             iks;
    };
}

#endif

