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

Sprite::Sprite(Image& image, size_t state)
: _image(&image)
, _w(image.iwidth())
, _h(image.iheight())
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
    if (_finished)
        return;
    _acc++;
    if (_acc == _speed)
    {
        _acc = 0;
        if (_currentImage + 1 == _baseImage + _length)
        {
            if (!_loop)
                _finished = true;
            else
                _currentImage = _baseImage;
        }
        else
            _currentImage++;
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
    FrameDescriptorf tex = _image->atlasAt(_currentImage);
    _w = tex.w * _image->width() * _scaleX;
    _h = tex.h * _image->height() * _scaleY;

    double dw = _w;
    double dh = _h;
    double x = _flipX ? 0 : tex.offX;
    double y = _flipY ? 0 : tex.offY;

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

    _vertex[0] = x;
    _vertex[1] = y;
    _vertex[2] = tex.x;
    _vertex[3] = tex.y;
    _vertex[4] = x + dw;
    _vertex[5] = y;
    _vertex[6] = tex.x + tex.w;
    _vertex[7] = tex.y;
    _vertex[8] = x + dw;
    _vertex[9] = y + dh;
    _vertex[10] = tex.x + tex.w;
    _vertex[11] = tex.y + tex.h;
    _vertex[12] = x;
    _vertex[13] = y + dh;
    _vertex[14] = tex.x;
    _vertex[15] = tex.y + tex.h;
}

