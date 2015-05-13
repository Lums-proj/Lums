/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Math.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_MATH_HPP
#define LUMS_MATH_HPP

#include <Lums/Vector.hpp>

namespace lm
{
    template <std::size_t N, typename T>
    float
    squareDist(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        float d = 0;
        float buf;

        for (std::size_t i = 0; i < N; ++i)
        {
            buf = v1[i] - v2[i];
            d += buf * buf;
        }
        return d;
    }

    template <std::size_t N, typename T>
    float
    dist(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        return std::sqrt(squareDist(v1, v2));
    }

    template <std::size_t N, typename T>
    float
    squareLength(const Vector<N, T>& vect)
    {
        float l = 0;
        float buf;

        for (std::size_t i = 0; i < N; ++i)
        {
            buf = vect[i];
            l += buf * buf;
        }
        return l;
    }

    template <std::size_t N, typename T>
    float
    length(const Vector<N, T>& vect)
    {
        return std::sqrt(squareLength(vect));
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    normal(const Vector<N, T>& vect)
    {
        float l = length(vect);
        Vector<N, T> v(vect);

        for (std::size_t i = 0; i < N; ++i)
            v[i] /= l;
        return v;
    }

    template <typename T>
    Vector3<T>
    cross(const Vector3<T>& u, const Vector3<T>&v)
    {
        Vector3<T> vect;

        vect[0] = u[1] * v[2] - u[2] * v[1];
        vect[1] = u[2] * v[0] - u[0] * v[2];
        vect[2] = u[0] * v[1] - u[1] * v[0];
        return vect;
    }

    template <std::size_t N, typename T>
    T
    dot(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        T val = T();

        for (std::size_t i = 0; i < N; ++i)
            val += lhs[i] * rhs[i];
        return val;
    }

    template <std::size_t N, typename T>
    bool
    null(const Vector<N, T>& vect)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (vect[i] != T())
                return false;
        }
        return true;
    }
}

#endif
