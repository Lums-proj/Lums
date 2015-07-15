/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Matrix.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_MATRIX_HPP
#define LUMS_MATRIX_HPP

#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
    /**
     * @cond
     */
    namespace internal
    {
        template <std::size_t N, typename T>
        class MatrixHelper
        {
        public:
            MatrixHelper(T* data)
            : _helper(data)
            {

            }

            T&
            operator[](std::size_t i)
            {
                return _helper[i];
            }

            const T&
            operator[](std::size_t i) const
            {
                return _helper[i];
            }

        private:
            T*  _helper;
        };
    }
    /**
     * @endcond
     */

    /**
     * @brief A class representing a square matrix
     * @tparam N The matrix dimension
     * @tparam T The matrix type
     */
    template <std::size_t N, typename T>
    class Matrix
    {
    public:
        /**
         * Create a null matrix
         */
        Matrix()
        : _data()
        {

        }

        /**
         * Multiply a matrix
         * @param rhs The other matrix
         * @return Self
         */
        Matrix<N, T>&
        operator*=(const Matrix<N, T>& rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        /**
         * Get a proxy line
         * @param i The line index
         * @return A matrix line
         */
        internal::MatrixHelper<N, T>
        operator[](std::size_t i)
        {
            return internal::MatrixHelper<N, T>(_data + i * N);
        }

        /**
         * Get a proxy line
         * @param i The line index
         * @return A matrix line
         */
        const internal::MatrixHelper<N, const T>
        operator[](std::size_t i) const
        {
            return internal::MatrixHelper<N, const T>(_data + i * N);
        }

        /**
         * Get a raw buffer from the matrix
         * @return The raw buffer
         */
        T*
        data()
        {
            return _data;
        }

        /**
         * Get a raw buffer from the matrix
         * @return The raw buffer
         */
        const T*
        data() const
        {
            return _data;
        }

        /**
         * Get the identity matrix
         * @return The identity matrix
         */
        static Matrix<N, T>
        identity()
        {
            Matrix<N, T> m;

            for (std::size_t i = 0; i < N; ++i)
                m[i][i] = 1;
            return m;
        }

    private:
        T   _data[N * N];
    };

    /**
     * Multiply two matrices
     * @param lhs The left matrix
     * @param rhs The right matrix
     * @return The product of the matrices
     */
    template <std::size_t N, typename T>
    Matrix<N, T>
    operator*(const Matrix<N, T>& lhs, const Matrix<N, T>& rhs)
    {
        Matrix<N, T> m;

        for (std::size_t j = 0; j < N; ++j)
        {
            for (std::size_t i = 0; i < N; ++i)
            {
                for (std::size_t k = 0; k < N; ++k)
                    m[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
        return m;
    }

    /**
     * Multiply a matrix and a scalar
     * @param lhs The matrix
     * @param rhs The scalar
     * @return The product
     */
    template <std::size_t N, typename T>
    Matrix<N, T>
    operator*(const Matrix<N, T>& lhs, T rhs)
    {
        Matrix<N, T> m;

        for (std::size_t j = 0; j < N; ++j)
        {
            for (std::size_t i = 0; i < N; ++i)
                m[i][j] = lhs[i][j] * rhs;
        }
        return m;
    }

    /**
     * Multiply a matrix and a scalar
     * @param lhs The scalar
     * @param rhs The matrix
     * @return The product
     */
    template <std::size_t N, typename T>
    Matrix<N, T>
    operator*(T lhs, const Matrix<N, T>& rhs)
    {
        Matrix<N, T> m;

        for (std::size_t j = 0; j < N; ++j)
        {
            for (std::size_t i = 0; i < N; ++i)
                m[i][j] = lhs * rhs[i][j];
        }
        return m;
    }

    template <std::size_t N, typename T>
    Vector<N, T>
    operator*(const Matrix<N, T>& mat, const Vector<N, T>& vect)
    {
        Vector<N, T> result;
        for (unsigned j = 0; j < N; ++j)
        {
            for (unsigned i = 0; i < N; ++i)
                result[j] += mat[i][j] * vect[i];
        }
        return result;
    }

    using Matrix2f = Matrix<2, float>;

    using Matrix3f = Matrix<3, float>;

    /**
     * A 4x4 float matrix
     */
    using Matrix4f = Matrix<4, float>;
}

#endif
