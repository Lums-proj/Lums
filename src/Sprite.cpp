#include <Lums/Sprite.hpp>
#include <Lums/GL.hpp>
#include <Lums/Image.hpp>

using namespace lm;

Sprite::Sprite(Image& image, int w, int h)
: _image(&image)
, _w(w)
, _h(h)
{

}

void
Sprite::draw(int x, int y) const
{
    GLint coords[] = {
        x, y,
        x + _w, y,
        x + _w, y + _h,
        x, y + _h
    };

    GLint texcoords[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_INT, 0, coords);
    glTexCoordPointer(2, GL_INT, 0, texcoords);
    _image->bind();
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
