/* ************************************************************************** */
/*                                                                            */
/*    Util/ParamTraits.hpp                           oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_UTIL_PARAM_TRAITS_HPP
#define LUMS_UTIL_PARAM_TRAITS_HPP

namespace lm
{
    namespace priv
    {
        template <typename T, int Size>
        struct ParamTraitsInternal {
            using const_type = typename ParamTraitsInternal<T, Size - 1>::const_type;
        };

        template <typename T>
        struct ParamTraitsInternal <T, 8> {
            using const_type = const T&;
        };

        template <typename T>
        struct ParamTraitsInternal <T, 0> {
            using const_type = T;
        };
    }

    template <typename T>
    struct ParamTraits {
        using const_type = typename priv::ParamTraitsInternal<T, sizeof(T)>::const_type;
    };
}

#endif
