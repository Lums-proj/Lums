/* ************************************************************************** */
/*                                                                            */
/*    Core/Identifier.hpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_CORE_IDENTIFIER_HPP
#define LUMS_CORE_IDENTIFIER_HPP

#include <functional>

namespace lm
{
    class Identifier
    {
        friend struct std::hash<Identifier>;

    public:
        Identifier(const char* str = "");
        
        bool
        operator==(Identifier rhs) const
        {
            return _index == rhs._index;
        }

        bool
        operator!=(Identifier rhs) const
        {
            return !(*this == rhs);
        }

        const char*     str() const;

private:
        size_t  _index;
    };
}

namespace std
{
    template <>
    struct hash <lm::Identifier>
    {
        size_t
        operator()(lm::Identifier id) const
        {
            return id._index;
        }
    };
}

#endif
