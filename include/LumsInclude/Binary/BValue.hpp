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

    using BInt = int;
    using BFloat = float;
    using BString = char*;

    class BValue
    {
    public:
        BValue();
        BValue(const BValue& rhs);
        BValue& operator=(const BValue& rhs);

        void    parse(std::ifstream& file);
        bool    is(BType type) const { return type == _type; }
        bool    isObject() const { return is(BType::Object); }
        bool    isArray() const { return is(BType::Array); }
        bool    isInt() const { return is(BType::Int); }
        bool    isFloat() const { return is(BType::Float); }
        bool    isString() const { return is(BType::String); }

        BInt            asInt() const;
        BFloat          asFloat() const;
        const BObject&  asObject() const;
        const BString   asString() const;
        const BArray&   asArray() const;

        const BValue&   operator[](int i) const;
        const BValue&   operator[](const char* str) const;

        ~BValue();

    private:
        BType           _type;
        union
        {
            BObject*    _object;
            BArray*     _array;
            BInt        _int;
            BFloat      _float;
            BString     _string;
        };
    };

    using BPair = std::pair<char*, BValue>;
}

#endif
