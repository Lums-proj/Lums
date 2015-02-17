/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sprite.cpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Sprite.hpp>
#include <Lums/GL.hpp>
#include <Lums/Image.hpp>

using namespace lm;

Sprite::Sprite(Image& image, int w, int h, size_t state)
: _image(&image)
, _w(w)
, _h(h)
, _baseImage(state)
, _currentImage(state)
, _length(1)
, _acc(0)
, _speed(0)
, _flipX(false)
, _flipY(false)
{
    updateTexCoord();
}

void
Sprite::update()
{
    _acc++;
    if (_acc == _speed)
    {
        _acc = 0;
        _currentImage++;
        if (_currentImage == _baseImage + _length)
            _currentImage = _baseImage;
        updateTexCoord();
    }
}

void
Sprite::draw(int x, int y) const
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTranslated(x, y, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_DOUBLE, sizeof(GLdouble) * 4, _vertex);
    glTexCoordPointer(2, GL_DOUBLE, sizeof(GLdouble) * 4, _vertex + 2);
    _image->bind();
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

/* PRIVATE */

void
Sprite::updateTexCoord()
{
    double dw = _w;
    double dh = _h;
    Rect2d tex = _image->atlasAt(_currentImage);

    if (_flipX)
    {
        tex.x += tex.w;
        tex.w = -tex.w;
    }

    if (_flipY)
    {
        tex.y += tex.h;
        tex.h = -tex.h;
    }

    _vertex[0] = 0;
    _vertex[1] = 0;
    _vertex[2] = tex.x;
    _vertex[3] = tex.y;
    _vertex[4] = dw;
    _vertex[5] = 0;
    _vertex[6] = tex.x + tex.w;
    _vertex[7] = tex.y;
    _vertex[8] = dw;
    _vertex[9] = dh;
    _vertex[10] = tex.x + tex.w;
    _vertex[11] = tex.y + tex.h;
    _vertex[12] = 0;
    _vertex[13] = dh;
    _vertex[14] = tex.x;
    _vertex[15] = tex.y + tex.h;
}

