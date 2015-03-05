/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sprite.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SPRITE_HPP
#define LUMS_SPRITE_HPP

#include <Lums/Image.hpp>
#include <Lums/ExportDll.hpp>



#include <iostream>

namespace lm
{
    class Sprite
    {
    public:

        Sprite()
        : _image(nullptr)
        , _w(0)
        , _h(0)
        , _baseImage(0)
        , _currentImage(0)
        , _length(1)
        , _acc(0)
        , _speed(0)
        , _flipX(false)
        , _flipY(false)
        , _finished(false)
        {

        }

        Sprite(Image& image, size_t state = 0);
        
        Image&
        image() const
        {
            return *_image;
        }

        int
        width() const
        {
            return _w;
        }

        int
        height() const
        {
            return _h;
        }

        void
        setImage(Image& image)
        {
            _image = &image;
            _w = _image->iwidth();
            _h = _image->iheight();
            setImageInAtlas(0);
        }

        void
        setAnimation(size_t image, size_t length, size_t speed, bool loop = true)
        {
            setSpeed(speed);
            _length = length;
            _loop = loop;
            _finished = false;
            setImageInAtlas(image);
        }

        void
        setSpeed(size_t speed)
        {
            _acc = 0;
            _speed = speed;
        }

        void
        setScale(double scale)
        {
            setScale(scale, scale);
        }

        void
        setScale(double scaleX, double scaleY)
        {
            _scaleX = scaleX;
            _scaleY = scaleY;
            updateTexCoord();
        }

        void
        setImageInAtlas(size_t i)
        {
            _baseImage = _currentImage = i;
            _acc = 0;
            updateTexCoord();
        }

        void
        flipX(bool b)
        {
            _flipX = b;
            updateTexCoord();
        }

        void
        flipY(bool b)
        {
            _flipY = b;
            updateTexCoord();
        }

        bool
        finished() const
        {
            return _finished;
        }

        LUMS_EXPORTED void  update();
        LUMS_EXPORTED void  draw(int x, int y) const;

        void
        draw() const
        {
            draw(0, 0);
        }

    private:
        void    updateTexCoord();

        Image*      _image;
        int         _w;
        int         _h;
        double      _scaleX;
        double      _scaleY;
        size_t      _baseImage;
        size_t      _currentImage;
        size_t      _length;
        size_t      _acc;
        size_t      _speed;
        GLdouble    _vertex[16];
        bool        _flipX;
        bool        _flipY;
        bool        _loop;
        bool        _finished;

    };
}

#endif
