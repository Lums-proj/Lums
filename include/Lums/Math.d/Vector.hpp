/* ************************************************************************** */
/*                                                                            */
/*    Math/Vector.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_MATH_VECTOR_HPP
#define LUMS_MATH_VECTOR_HPP

#include <Lums/Util.d/ParamTraits.hpp>

namespace lm
{
    template <int, typename>
    class Vector;

    namespace priv
    {
        template <int N, typename T>
        struct VectorData
        {
            T   _data[N];
        };

        template <typename T>
        struct VectorData<1, T>
        {
            union
            {
                T   x;
                T   r;
                T   _data[1];
            };
        };

        template <typename T>
        struct VectorData<2, T>
        {
            union
            {
                struct
                {
                    T   x;
                    T   y;
                };
                struct
                {
                    T   r;
                    T   g;
                };
                T       _data[2];
            };
        };

        template <typename T>
        struct VectorData<3, T>
        {
            union
            {
                struct
                {
                    T           x;
                    T           y;
                    T           z;
                };
                struct
                {
                    T           r;
                    T           g;
                    T           b;
                };
                T               _data[3];
            };
        };

        template <typename T>
        struct VectorData<4, T>
        {
            union
            {
                struct
                {
                    T           x;
                    T           y;
                    T           z;
                    T           w;
                };
                struct
                {
                    T           r;
                    T           g;
                    T           b;
                    T           a;
                };
                T               _data[4];
            };
        };

        template <typename T, int Size>
        struct VectorInit {
            template <typename... Ts>
            static void init(T* data, typename ParamTraits<T>::const_type head, Ts... values) {
                static_assert(Size >= 1, "too many parameters");
                *data = head;
                VectorInit<T, Size - 1>::init(data + 1, values...);
            }

            template <int NN, typename TT, typename... Ts>
            static void init(T* data, const Vector<NN, TT>& vect, Ts... values) {
                static_assert(Size >= NN, "too many parameters");
                for (unsigned i = 0; i < NN; ++i)
                    data[i] = vect[i];
                VectorInit<T, Size - NN>::init(data + NN, values...);
            }

            static void init(T* data) {
                for (unsigned i = 0; i < Size; ++i)
                    data[i] = T();
            }
        };
    }

    template <int N, typename T>
    class Vector : public priv::VectorData<N, T>
    {
    public:
        enum  { size = N };

        using type              = T;
        using const_type        = typename ParamTraits<T>::const_type;
        using reference_type    = T&;

        static_assert(N > 0, "Vectors must have a positive, nonzero size.");

        Vector()
        {
            for (unsigned i = 0; i< N; ++i)
                this->_data[i] = T();
        }

        template <typename... Ts>
        Vector(Ts... values)
        {
            priv::VectorInit<T, N>::init(this->_data, values...);
        }

        template <typename TT>
        Vector<N, T>&   operator=(const Vector<N, TT>& rhs)
        {
            for (unsigned i = 0; i < N; ++i)
                this->_data[i] = rhs._data[i];
        }

        reference_type operator[](int i)
        {
            return this->_data[i];
        }

        const_type operator[](int i) const
        {
            return this->_data[i];
        }

        Vector<N, T>& operator+=(const_type rhs)
        {
            for (int i = 0; i < N; ++i)
                this->_data[i] += rhs;
            return *this;
        }

        Vector<N, T>& operator-=(const_type rhs)
        {
            for (int i = 0; i < N; ++i)
                this->_data[i] -= rhs;
            return *this;
        }

        Vector<N, T>& operator*=(const_type rhs)
        {
            for (int i = 0; i < N; ++i)
                this->_data[i] *= rhs;
            return *this;
        }

        Vector<N, T>& operator/=(const_type rhs)
        {
            for (int i = 0; i < N; ++i)
                this->_data[i] /= rhs;
            return *this;
        }
    };

    template <int N, typename T>
    Vector<N, T> operator+(const Vector<N, T>& lhs, typename ParamTraits<T>::const_type rhs)
    {
        Vector<N, T> v(lhs);
        v += rhs;
        return v;
    }

    template <int N, typename T>
    Vector<N, T> operator+(typename ParamTraits<T>::const_type lhs, const Vector<N, T>& rhs)
    {
        Vector<N, T> v(rhs);
        v += lhs;
        return v;
    }

    using Vector1f = Vector<1, float>;
    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
    using Vector4f = Vector<4, float>;

    using Vector1i = Vector<1, int>;
    using Vector2i = Vector<2, int>;
    using Vector3i = Vector<3, int>;
    using Vector4i = Vector<4, int>;
}

#endif
