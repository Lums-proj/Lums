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
#include <Lums/Vector2.hpp>

namespace lm
{
    class Sprite
    {
    public:

        Sprite();
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

        size_t
        atlas() const
        {
            return _currentImage;
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
        setImageInAtlas(size_t i)
        {
            _baseImage = _currentImage = i;
            _acc = 0;
        }

        bool
        finished() const
        {
            return _finished;
        }

        LUMS_EXPORTED void  update();

        lm::Vector2f    pos;
        lm::Vector2f    scale;
        lm::Vector2b    flip;

    private:
        Image*      _image;
        int         _w;
        int         _h;
        size_t      _baseImage;
        size_t      _currentImage;
        size_t      _length;
        size_t      _acc;
        size_t      _speed;
        bool        _loop;
        bool        _finished;

    };
}

#endif
