/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BObject.hpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BOBJECT_HPP
#define LUMS_BOBJECT_HPP

#include <fstream>
#include <LumsInclude/Binary/BValue.hpp>

namespace lm
{
    class BObject
    {
    public:
        BObject();
        void    parse(std::ifstream& file);
        const BValue& operator[](const BString str) const;
        ~BObject();
    private:
        int        _size;
        BPair*    _values;
    };
}

#endif
