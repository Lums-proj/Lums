/* ************************************************************************** */
/*                                                                            */
/*    Math/Rect.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_MATH_RECT_HPP
#define LUMS_MATH_RECT_HPP

#include <Lums/Math.d/Vector.hpp>

namespace lm
{
    template <int N, typename T>
    struct Rect
    {
        Vector<N, T>    position;
        Vector<N, T>    size;
    };

    using Rect2f = Rect<2, float>;
    using Rect3f = Rect<3, float>;
    using Rect4f = Rect<4, float>;

    using Rect2i = Rect<2, int>;
    using Rect3i = Rect<3, int>;
    using Rect4i = Rect<4, int>;
}

#endif
