/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Nyan.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Lums.hpp>

class Nyan : public lm::GameState
{
public:
    Nyan()
    : _linear(true)
    {
        
    }

    void
    load()
    {
        glMatrixMode(GL_PROJECTION);
        glOrtho(0, 400, 400, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_TEXTURE_2D);
        _image.loadFile("Nyan.png");
        _sprite.setImage(_image);
        _sprite.setSize(400, 400);
    }

    void
    update()
    {

    }

    void
    handleEvent(const lm::Event& event)
    {
        if (event.type == lm::Event::Type::KeyDown)
        {
            if (event.key == lm::Key::V)
            {
                _linear = !_linear;
                _image.linear(_linear);
            }
            else
                lm::Core::get().stop();
        }
    }

    void
    render() const
    {
        _sprite.draw(0, 0);
    }

private:
    lm::Image   _image;
    lm::Sprite  _sprite;
    bool        _linear;
};

int
main()
{
    lm::Core core(400, 400, "Nyan");

    core.push<Nyan>();
    core.start();
}