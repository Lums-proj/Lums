/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GL.cpp                                       &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <Lums/GL.h>


void    lm::glPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    constexpr const GLdouble    pi = 3.1415926535897932384626433832795;
    GLdouble                    fw;
    GLdouble                    fh;

    fh = tan(fovY / 360 * pi) * zNear;
    fw = fh * aspect;
    glFrustum(-fw, fw, -fh, fh, zNear, zFar);
}

void    lm::glLookAt(Vector3f eye, Vector3f lookAt, Vector3f up)
{
    Vector3f    f;
    Vector3f    s;
    Vector3f    u;

    f = lookAt - eye;
    f.Normalize();
    up.Normalize();
    s = f.Cross(up);
    u = s.Cross(f);
    float m[] = {
        s.x, u.x, -f.x, 0,
        s.y, u.y, -f.y, 0,
        s.z, u.z, -f.z, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(m);
    glTranslatef(-eye.x, -eye.y, -eye.z);
}