/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BArray.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BARRAY_HPP
#define LUMS_BARRAY_HPP

#include <fstream>
#include <LumsInclude/Binary/BValue.hpp>

namespace lm
{
    class BArray
    {
    public:
        BArray();
        BArray(const BArray& rhs);
        BArray&         operator=(const BArray& rhs);

        void            parse(std::ifstream& file);
        const BValue&   operator[](int i) const { return _values[i]; }
        int             size() const { return _size; }
        ~BArray();

    private:
        int     _size;
        BValue* _values;   
    };   
}

#endif