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

#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
    /**
     * Compute the square distance between two points
     * @param v1 The first point
     * @param v2 The second point
     * @return The square distance between two points
     */
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

    /**
     * Compute the distance between two points
     * @param v1 The first point
     * @param v2 The second point
     * @return The distance between two points
     */
    template <std::size_t N, typename T>
    float
    dist(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        return std::sqrt(squareDist(v1, v2));
    }

    /**
     * Compute the square length of a vector
     * @param vect The vector
     * @return The square length of the vector
     */
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

    /**
     * Compute the length of a vector
     * @param vect The vector
     * @return The length of the vector
     */
    template <std::size_t N, typename T>
    float
    length(const Vector<N, T>& vect)
    {
        return std::sqrt(squareLength(vect));
    }

    /**
     * Compute the normal of a vector
     * @param vect The vector
     * @return The normal of the vector
     */
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

    /**
     * Compute the cross product between two vectors
     * @param u The first vector
     * @param v The second vector
     * @return The cross product between two vectors
     */
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

    /**
     * Compute the dot product between two vectors
     * @param lhs The first vector
     * @param rhs The second vector
     * @return The dot product between two vectors
     */
    template <std::size_t N, typename T>
    T
    dot(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        T val = T();

        for (std::size_t i = 0; i < N; ++i)
            val += lhs[i] * rhs[i];
        return val;
    }

    /**
     * Check wether a vector is the null vector
     * @param vect The vector
     * @return True if the vector is null
     */
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
