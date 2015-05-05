/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GL.hpp                                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GL_HPP
#define LUMS_GL_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#endif

#include <Lums/Math.hpp>
#include <Lums/ExportDll.hpp>

namespace lm
{
    /**
     * GLU backport.
     * Emulate the old gluPerspective.
     */
    LUMS_EXPORTED void    glPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    
    /**
     * GLU backport.
     * Emulate the old gluLookAt.
     */
    LUMS_EXPORTED void    glLookAt(Vector3f eye, Vector3f lookAt, Vector3f up);

    /**
     * GLU backport.
     * Emulate the old gluLookAt.
     */
    inline void
    glLookAt(float eyeX, float eyeY, float eyeZ,
             float lookAtX, float lookAtY, float lookAtZ,
             float upX, float upY, float upZ)
    {
        glLookAt(Vector3f(eyeX, eyeY, eyeZ),
                 Vector3f(lookAtX, lookAtY, lookAtZ),
                 Vector3f(upX, upY, upZ));
    }
}

#endif