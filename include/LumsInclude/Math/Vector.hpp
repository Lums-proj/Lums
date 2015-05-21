/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Vector.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_VECTOR_HPP
#define LUMS_VECTOR_HPP

#include <cmath>
#include <type_traits>
#include <LumsInclude/Math/Angle.hpp>

namespace lm
{
    template <std::size_t N, typename T>
    class Vector;

    namespace internal
    {
        template <typename T>
        struct vector_traits
        {
            enum { value = false };
        };

        template <std::size_t N, typename T>
        struct vector_traits <Vector<N, T>>
        {
            enum { value = true };
        };

        template <std::size_t N, typename T>
        struct VectorData
        {
            VectorData()
            : _data()
            {

            }

            T   _data[N];
        };

        template <typename T>
        struct VectorData<2, T>
        {
            VectorData()
            : _data()
            {

            }

            union
            {
                T   _data[2];
                struct
                {
                    T   x;
                    T   y;
                };
            };
        };

        template <typename T>
        struct VectorData<3, T>
        {
            VectorData()
            : _data()
            {

            }

            union
            {
                T   _data[3];
                struct
                {
                    T   x;
                    T   y;
                    T   z;
                };
            };
        };

        template <typename T>
        struct VectorData<4, T>
        {
            VectorData()
            : _data()
            {

            }
            
            union
            {
                T   _data[4];
                struct
                {
                    T   x;
                    T   y;
                    T   z;
                    T   w;
                };
            };
        };
    }

    /**
     * This class represents a Vector.
     */
    template <std::size_t N, typename T>
    class Vector : public internal::VectorData<N, T>
    {
    public:
        /**
         * Construct a vector from a value
         * The value is assigned to each member.
         * @param value The value to be assigned.
         */
        Vector(T value = T())
        {
            for (std::size_t i = 0; i < N; ++i)
                this->_data[i] = value;
        }

        template <typename A, typename B, typename... Types>
        Vector(A a, B b, Types... values)
        {
            _fill<N, A, B, Types...>(a, b, values...);
        }

        T&
        operator[](std::size_t i)
        {
            return this->_data[i];
        }

        constexpr const T&
        operator[](std::size_t i) const
        {
            return this->_data[i];
        }

    private:
        template <std::size_t Count, typename Head, typename... Tail>
        void
        _fill(Head head, Tail... tail)
        {
            this->_data[N - Count] = head;
            _fill<Count - 1, Tail...>(tail...);
        }

        template <std::size_t Count, typename... Tail>
        typename std::enable_if<Count == 0>::type
        _fill(Tail... tail)
        {

        }
    };

    template <std::size_t N, typename T>
    Vector<N, T>&
    operator+=(Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] += rhs[i];
        return lhs;
    }

    template <std::size_t N, typename T>
    Vector<N, T>&
    operator-=(Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] -= rhs[i];
        return lhs;
    }

    template <std::size_t N, typename T, typename U>
    Vector<N, T>&
    operator*=(Vector<N, T>& lhs, U rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] *= rhs;
        return lhs;
    }

    template <std::size_t N, typename T, typename U>
    Vector<N, T>&
    operator/=(Vector<N, T>& lhs, U rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] /= rhs;
        return lhs;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator+(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        Vector<N, T> vec(lhs);

        vec += rhs;
        return vec;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator-(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        Vector<N, T> vec(lhs);

        vec -= rhs;
        return vec;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator*(const Vector<N, T>& lhs, float rhs)
    {
        Vector<N, T> vec(lhs);

        vec *= rhs;
        return vec;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator/(const Vector<N, T>& lhs, float rhs)
    {
        Vector<N, T> vec(lhs);

        vec /= rhs;
        return vec;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator+(const Vector<N, T>& vect)
    {
        Vector<N, T> v(vect);

        return v;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator-(const Vector<N, T>& vect)
    {
        Vector<N, T> v(vect);

        for (std::size_t i = 0; i < N; ++i)
            v[i] = -v[i];
        return v;
    }

    template <typename T> using Vector2 = Vector<2, T>;
    template <typename T> using Vector3 = Vector<3, T>;
    template <typename T> using Vector4 = Vector<4, T>;

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector2b = Vector2<bool>;
    using Vector2a = Vector2<Angle>;

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
    using Vector3b = Vector3<bool>;
    using Vector3a = Vector3<Angle>;

    using Vector4f = Vector4<float>;
    using Vector4i = Vector4<int>;
    using Vector4b = Vector4<bool>;
    using Vector4a = Vector4<Angle>;
}

#endif