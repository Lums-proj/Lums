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
    /**
     * @brief A struct defining a rectangle
     */
    template <std::size_t N, typename T>
    struct Rect
    {
        /**
         * The underlying vector type
         */
        using Vect = Vector<N, T>;

        /**
         * The position
         */
        Vect    pos;

        /**
         * The size
         */
        Vect    size;
    };

    /**
     * @cond
     */
    template <typename T> using Rect2 = Rect<2, T>;
    template <typename T> using Rect3 = Rect<3, T>;
    /**
     * @endcond
     */
    
    /**
     * A rectangle of floats
     */
    using Rect2f = Rect2<float>;

    /**
     * A rectangle of ints
     */
    using Rect2i = Rect2<int>;
}

#endif
