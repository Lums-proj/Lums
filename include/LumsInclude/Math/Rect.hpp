/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Rect.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_RECT_HPP
#define LUMS_RECT_HPP

#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
    template <std::size_t N, typename T>
    struct Rect
    {
        using Vect = Vector<N, T>;

        Vect    pos;
        Vect    size;
    };

    template <typename T> using Rect2 = Rect<2, T>;
    template <typename T> using Rect3 = Rect<3, T>;
    
    using Rect2f = Rect2<float>;
}

#endif
