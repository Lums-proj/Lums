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

#include <fstream>

namespace lm
{
    class BArray;
    class BObject;

    enum class BType
    {
        None,
        Object,
        Array,
        Int,
        Float,
        String
    };

    using BInteger = int;
    using BFloating = float;
    using BString = char*;

    class BValue
    {
    public:
        BValue();
        void    parse(std::ifstream& file);
        ~BValue();

    private:
        BType           _type;
        union
        {
            BObject*    _object;
            BArray*     _array;
            BInteger    _int;
            BFloating   _float;
            BString     _string;
        };
    };
}

#endif
