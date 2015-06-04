/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    OpenGL.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_OPENGL_HPP
#define LUMS_OPENGL_HPP

#ifdef __APPLE__
# include <OpenGL/gl3.h>
# include <OpenGL/gl3ext.h>
#endif

#ifdef WIN32
# include <windows.h>
# include <gl/gl.h>
#endif

#include <LumsInclude/Math/Math.hpp>
#include <LumsInclude/Math/Matrix.hpp>

#ifndef LUMS_PI
# define LUMS_PI 3.14159265358979323846f
#endif

namespace lm
{
    /**
     * Create a frustum projection matrix
     * @param left The left position
     * @param right The right position
     * @param bottom The bottom position
     * @param top The top position
     * @param znear The near clipping plane
     * @param zfar The far clipping plane
     * @return A frustum projection matrix
     */
    inline Matrix4f
    frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar)
    {
        Matrix4f matrix;

        matrix[0][0] = 2.f * znear / (right - left);
        matrix[1][1] = 2.f * znear / (top - bottom);
        matrix[2][0] = (right + left) / (right - left);
        matrix[2][1] = (top + bottom) / (top - bottom);
        matrix[2][2] = -(zfar + znear) / (zfar - znear);
        matrix[2][3] = -1.f;
        matrix[3][2] = -(2.f * zfar * znear) / (zfar - znear);
        return matrix;
    }

    /**
     * Create a perspective projection matrix
     * @param fov The field of view in degrees
     * @param aspect The aspect ratio
     * @param znear The near clipping plane
     * @param zfar The far clipping plane
     * @return A perspective projection matrix
     */
    inline Matrix4f
    perspective(GLfloat fov, GLfloat aspect, GLfloat znear, GLfloat zfar)
    {
        const float ymax = znear * std::tanf(fov * LUMS_PI / 360.f);
        const float xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    /**
     * Create a orthogonal projection matrix
     * @param left The left position
     * @param right The right position
     * @param bottom The bottom position
     * @param top The top position
     * @return A orthogonal projection matrix
     */
    inline Matrix4f
    ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
    {
        Matrix4f result = Matrix4f::identity();

        result[0][0] = 2.f / (right - left);
        result[1][1] = 2.f / (top - bottom);
        result[2][2] = -1.f;
        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        return result;
    }

    /**
     * Translate a matrix by an offset 
     * @param matrix The matrix to be translated
     * @param x The x offset
     * @param x The y offset
     * @param x The z offset
     */
    inline void
    translate(Matrix4f& matrix, GLfloat x, GLfloat y, GLfloat z)
    {
        Matrix4f id = Matrix4f::identity();

        id[3][0] = x;
        id[3][1] = y;
        id[3][2] = z;

        matrix *= id;
    }

    /**
     * Translate a matrix by a vector 
     * @param matrix The matrix to be translated
     * @param x The translation vector
     */
    inline void
    translate(Matrix4f& matrix, Vector3f vec)
    {
        translate(matrix, vec.x, vec.y, vec.z);
    }

    /**
     * Rotate a matrix by an angle around a vector
     * @param The matrix to be rotated
     * @param angle The angle in degrees
     * @param v The up vector
     */
    inline void
    rotate(Matrix4f& matrix, float angle, Vector3f v)
    {
        angle = angle * LUMS_PI / 180.f;
        const float c = std::cos(angle);
        const float s = std::sin(angle);

        Vector3f axis(normal(v));
        Vector3f temp(axis * (1.f - c));

        Matrix4f rot;

        rot[0][0] = c + temp[0] * axis[0];
        rot[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
        rot[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

        rot[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
        rot[1][1] = c + temp[1] * axis[1];
        rot[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

        rot[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
        rot[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
        rot[2][2] = c + temp[2] * axis[2];

        rot[3][3] = 1.f;

        matrix *= rot;
    }

    /**
     * Create a view matrix
     * @param eye The eye position
     * @param center The field of view center in space coordinates
     * @param up The up vector
     * @return A view matrix
     */
    inline Matrix4f
    lookAt(Vector3f eye, Vector3f center, Vector3f up)
    {
        const Vector3f f(normal(center - eye));
        const Vector3f s(normal(cross(f, up)));
        const Vector3f u(cross(s, f));

        Matrix4f result = Matrix4f::identity();

        result[0][0] = s.x;
        result[1][0] = s.y;
        result[2][0] = s.z;
        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;
        result[0][2] =-f.x;
        result[1][2] =-f.y;
        result[2][2] =-f.z;
        result[3][0] =-dot(s, eye);
        result[3][1] =-dot(u, eye);
        result[3][2] = dot(f, eye);

        return result;
    }
}

#endif
