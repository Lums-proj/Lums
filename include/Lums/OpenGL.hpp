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
    perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
    {
        static const float pi = 3.14159265358979323846f;
        Matrix4f matrix;
        GLfloat range = std::tanf(fov * pi *  1.0f / 360.0f) * near;

        matrix[0][0] = (2 * near) / ((range * aspect) - (-range * aspect));
        matrix[1][1] = (2 * near) / (2 * range);
        matrix[2][2] = -(far + near) / (far - near);
        matrix[2][3] = -1;
        matrix[3][2] = -(2 * far * near) / (far - near);
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
}

#endif
