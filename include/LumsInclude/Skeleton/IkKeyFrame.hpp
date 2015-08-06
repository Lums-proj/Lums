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

namespace lm
{
    struct IkKeyFrame
    {
        int             frame;
        bool            bendPositive;
        KeyFrameCurve   curve;
    };
}

#endif
