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

namespace lm
{
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

    template <std::size_t N, typename T>
    class Matrix
    {
    public:
        Matrix()
        : _data()
        {

        }

        Matrix<N, T>&
        operator*=(const Matrix<N, T>& rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        internal::MatrixHelper<N, T>
        operator[](std::size_t i)
        {
            return internal::MatrixHelper<N, T>(_data + i * N);
        }

        const internal::MatrixHelper<N, const T>
        operator[](std::size_t i) const
        {
            return internal::MatrixHelper<N, const T>(_data + i * N);
        }

        T*
        data()
        {
            return _data;
        }

        const T*
        data() const
        {
            return _data;
        }

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

    using Matrix4f = Matrix<4, float>;
}

#endif
