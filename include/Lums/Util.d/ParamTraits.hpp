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
        struct ParamTraits {
            using const_type = typename ParamTraits<T, Size - 1>::const_type;
        };

        template <typename T>
        struct ParamTraits <T, 8> {
            using const_type = const T&;
        };

        template <typename T>
        struct ParamTraits <T, 0> {
            using const_type = T;
        };
    }

    template <typename T>
    struct ParamTraits {
        using const_type = typename priv::ParamTraits<T, sizeof(T)>::const_type;
    };
}

#endif
