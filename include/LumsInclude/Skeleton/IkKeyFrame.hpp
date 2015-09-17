/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    IkKeyFrame.hpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_IK_KEY_FRAME_HPP
#define LUMS_SKELETON_IK_KEY_FRAME_HPP

#include <LumsInclude/Skeleton/KeyFrame.hpp>

namespace lm
{
    struct IkKeyFrame : public KeyFrame
    {
        void    loadFromFile(std::ifstream& file);

        bool            bendPositive;
    };
}

#endif
