/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    KeyFrameCurve.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_KEY_FRAME_CURVE_HPP
#define LUMS_KEY_FRAME_CURVE_HPP

namespace lm
{
    struct KeyFrameCurve
    {
        enum class Type : unsigned char
        {
            Linear,
            Stepped,
            Bezier
        };

        Type        type;
        Vector2f    c0;
        Vector2f    c1;
    };
}

#endif
