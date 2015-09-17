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

#include <LumsInclude/Skeleton/KeyFrame.hpp>
#include <LumsInclude/Skeleton/KeyFrameCurve.hpp>

namespace lm
{
    struct RotationKeyFrame : public KeyFrame
    {
        void            loadFromFile(std::ifstream& file);
        
        float           rotation;
        KeyFrameCurve   curve;
    };
}

#endif
