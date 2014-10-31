/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GL.h                                         &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GL_H
#define LUMS_GL_H

#include <SDL2/SDL_opengl.h>
#include <Lums/Vector3.h>

namespace lm
{
    /**
     * GLU backport.
     * Emulate the old gluPerspective.
     */
    void    glPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    
    /**
     * GLU backport.
     * Emulate the old gluLookAt.
     */
    void    glLookAt(Vector3f eye, Vector3f lookAt, Vector3f up);

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