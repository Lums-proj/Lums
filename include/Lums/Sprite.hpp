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

namespace lm
{
    class Image;

    class Sprite
    {
    public:

        Sprite()
        : _image(nullptr)
        , _w(0)
        , _h(0)
        {

        }

        Sprite(Image& image, int w = 0, int h = 0);
        
        Image&
        image() const
        {
            return *_image;
        }

        void
        setImage(Image& image)
        {
            _image = &image;
        }

        int
        width() const
        {
            return _w;
        }

        int
        height()
        {
            return _h;
        }

        void
        setSize(int w, int h)
        {
            _w = w;
            _h = h;
        }

        void    draw(int x, int y) const;

    private:
        Image*  _image;
        int     _w;
        int     _h;
    };
}

#endif
