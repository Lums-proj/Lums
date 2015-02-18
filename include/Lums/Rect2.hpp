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

#ifndef LUMS_RECT2_HPP
#define LUMS_RECT2_HPP

#include <Lums/Vector2.hpp>

namespace lm
{
    template <typename T>
    struct Rect2
    {
        Rect2()
        : x(T())
        , y(T())
        , w(T())
        , h(T())
        {

        }

        Rect2(T x, T y)
        : x(x)
        , y(y)
        , w(T())
        , h(T())
        {

        }

        Rect2(T x, T y, T w, T h)
        : x(x)
        , y(y)
        , w(w)
        , h(h)
        {

        }

        Vector2<T>
        pos() const
        {
            return {x, y};
        }

        Vector2<T>
        length() const
        {
            return {w, h};
        }

        T     x;
        T     y;
        T     w;
        T     h;
    };

    typedef Rect2<int>      Rect2i;

    typedef Rect2<float>    Rect2f;

    typedef Rect2<double>   Rect2d;
}

#endif
