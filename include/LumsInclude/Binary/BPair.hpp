/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BPair.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BPAIR_HPP
#define LUMS_BPAIR_HPP

#include <LumsInclude/Binary/BValue.hpp>

namespace lm
{
    struct BPair
    {
        char*   key;
        BValue  value;
    };
}

#endif
