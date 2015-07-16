/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    RotationKeyFrame.hpp                           oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_ROTATION_KEY_FRAME_HPP
#define LUMS_ROTATION_KEY_FRAME_HPP

#include <LumsInclude/Skeleton/KeyFrameCurve.hpp>

namespace lm
{
    struct RotationKeyFrame
    {
        unsigned        time;
        float           angle;
        KeyFrameCurve   curve;
    };
}

#endif
