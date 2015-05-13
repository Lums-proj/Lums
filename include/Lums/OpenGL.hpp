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

#include <Lums/Math.hpp>
#include <Lums/Matrix.hpp>

namespace lm
{
    inline Matrix4f
    perspective(GLfloat fov, GLfloat aspect, GLfloat znear, GLfloat zfar)
    {
        static const float pi = 3.14159265358979323846f;
        Matrix4f matrix;
        
        const float radfov = fov * pi / 180.f;
        const float half = std::tanf(radfov / 2.f);

        matrix[0][0] = 1.f / (aspect * half);
        matrix[1][1] = 1.f / (half);
        matrix[2][2] = -(zfar + znear) / (zfar - znear);
        matrix[3][2] = -1.f;
        matrix[2][3] = -(2.f * zfar * znear) / (zfar - znear);
        return matrix;
    }

    inline void
    translate(Matrix4f& matrix, GLfloat x, GLfloat y, GLfloat z)
    {
        Matrix4f id = Matrix4f::identity();

        id[3][0] = x;
        id[3][1] = y;
        id[3][2] = z;

        matrix *= id;
    }

    inline void
    translate(Matrix4f& matrix, Vector3f vec)
    {
        translate(matrix, vec.x, vec.y, vec.z);
    }

    inline Matrix4f
    lookAt(float eyex, float eyey, float eyez, float pointx, float pointy, float pointz, float upx, float upy, float upz)
    {
        Matrix4f result;
        Vector3f forward(pointx - eyex, pointy - eyey, pointz - eyez);
        Vector3f up(upx, upy, upz);
        Vector3f side;

        forward = normal(forward);
        side = normal(cross(forward, up));
        up = cross(side, forward);
        result[0][0] = side[0];
        result[0][1] = up[0];
        result[0][2] = -forward[0];
        result[1][0] = side[1];
        result[1][1] = up[1];
        result[1][2] = -forward[1];
        result[2][0] = side[2];
        result[2][1] = up[2];
        result[2][2] = -forward[2];
        result[3][0] = -eyex;
        result[3][1] = -eyey;
        result[3][2] = -eyez;
        result[3][3] = 1.f;
        return result;
    }
}

#endif
