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
    /**
     * @cond
     */
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
     * @endcond
     */

    /**
     * @brief A class representing a Vector.
     * @tparam N The vector dimension
     * @tparam T The vector type
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

        /**
         * Construct a vector from a batch of values
         * @param a The first value
         * @param b The second value
         * @param values The remaining values
         */
        template <typename A, typename B, typename... Types>
        Vector(A a, B b, Types... values)
        {
            _fill<N, A, B, Types...>(a, b, values...);
        }

        /**
         * Get a value from the vector
         * @param i The index
         * @return A value
         */
        T&
        operator[](std::size_t i)
        {
            return this->_data[i];
        }

        /**
         * Get a value from the vector
         * @param i The index
         * @return A value
         */
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
    bool
    operator==(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (!(lhs[i] == rhs[i]))
                return false;
        }
        return true;
    }

    /**
     * Add and assign vectors
     * @param lhs The first vector
     * @param rhs The second vector
     * @return The first vector
     */
    template <std::size_t N, typename T>
    Vector<N, T>&
    operator+=(Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] += rhs[i];
        return lhs;
    }

    /**
     * Substract and assign vectors
     * @param lhs The first vector
     * @param rhs The second vector
     * @return The first vector
     */
    template <std::size_t N, typename T>
    Vector<N, T>&
    operator-=(Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] -= rhs[i];
        return lhs;
    }

    /**
     * Multiply and assign a vector and a scalar
     * @param lhs The vector
     * @param rhs The scalar
     * @return The vector
     */
    template <std::size_t N, typename T, typename U>
    Vector<N, T>&
    operator*=(Vector<N, T>& lhs, U rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] *= rhs;
        return lhs;
    }

    /**
     * Divide and assign a vector and a scalar
     * @param lhs The vector
     * @param rhs The scalar
     * @return The vector
     */
    template <std::size_t N, typename T, typename U>
    Vector<N, T>&
    operator/=(Vector<N, T>& lhs, U rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            lhs[i] /= rhs;
        return lhs;
    }

    /**
     * Add vectors
     * @param lhs The first vector
     * @param rhs The second vector
     * @return The sum
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator+(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        Vector<N, T> vec(lhs);

        vec += rhs;
        return vec;
    }

    /**
     * Substract vectors
     * @param lhs The first vector
     * @param rhs The second vector
     * @return The difference
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator-(const Vector<N, T>& lhs, const Vector<N, T>& rhs)
    {
        Vector<N, T> vec(lhs);

        vec -= rhs;
        return vec;
    }

    /**
     * Multiply a vector and a scalar
     * @param lhs The vector
     * @param rhs The scalar
     * @return The product
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator*(const Vector<N, T>& lhs, float rhs)
    {
        Vector<N, T> vec(lhs);

        vec *= rhs;
        return vec;
    }

    /**
     * Divide and assign a vector and a scalar
     * @param lhs The vector
     * @param rhs The scalar
     * @return The quotient
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator/(const Vector<N, T>& lhs, float rhs)
    {
        Vector<N, T> vec(lhs);

        vec /= rhs;
        return vec;
    }

    /**
     * Unary plus
     * @param vect A vector
     * @return The same vector
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator+(const Vector<N, T>& vect)
    {
        Vector<N, T> v(vect);

        return v;
    }

    /**
     * Unary minus
     * @param vect A vector
     * @return The opposite vector
     */
    template <std::size_t N, typename T>
    Vector<N, T>
    operator-(const Vector<N, T>& vect)
    {
        Vector<N, T> v(vect);

        for (std::size_t i = 0; i < N; ++i)
            v[i] = -v[i];
        return v;
    }

    /**
     * @cond
     */
    template <typename T> using Vector2 = Vector<2, T>;
    template <typename T> using Vector3 = Vector<3, T>;
    template <typename T> using Vector4 = Vector<4, T>;
    /**
     * @endcond
     */

    /**
     * A 2D vector of floats
     */
    using Vector2f = Vector2<float>;

    /**
     * A 2D vector of ints
     */
    using Vector2i = Vector2<int>;

    /**
     * A 2D vector of bools
     */
    using Vector2b = Vector2<bool>;

    /**
     * A 2D vector of angles
     */
    using Vector2a = Vector2<Angle>;

    /**
     * A 3D vector of floats
     */
    using Vector3f = Vector3<float>;

    /**
     * A 3D vector of ints
     */
    using Vector3i = Vector3<int>;

    /**
     * A 3D vector of bools
     */
    using Vector3b = Vector3<bool>;

    /**
     * A 3D vector of angles
     */
    using Vector3a = Vector3<Angle>;

    /**
     * A 4D vector of floats
     */
    using Vector4f = Vector4<float>;

    /**
     * A 4D vector of ints
     */
    using Vector4i = Vector4<int>;

    /**
     * A 4D vector of bools
     */
    using Vector4b = Vector4<bool>;

    /**
     * A 4D vector of angles
     */
    using Vector4a = Vector4<Angle>;
}

#endif