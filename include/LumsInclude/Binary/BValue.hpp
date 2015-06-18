/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BValue.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BVALUE_HPP
#define LUMS_BVALUE_HPP

#include <LumsInclude/Binary/BObject.hpp>

namespace lm
{
    using BInteger = int;
    using BFloating = float;
    using BString = char*;

    enum class BType
    {
        Object,
        Array,
        Integer,
        Floating,
        String
    };

    struct BValue
    {
        BType type;
        union
        {
            BObject     object;
            BArray      array;
            BInteger    integer;
            BFloating   floating;
            BString     string;
        };
    };
}

#endif
