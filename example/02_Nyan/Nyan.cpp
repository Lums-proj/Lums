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
        _image.loadFile("Nyan.png");
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glEnable(GL_TEXTURE_2D);
        _image.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(-1, -1);
        glTexCoord2f(1, 0);
        glVertex2f(1, -1);
        glTexCoord2f(1, 1);
        glVertex2f(1, 1);
        glTexCoord2f(0, 1);
        glVertex2f(-1, 1);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    }

private:
    lm::Image   _image;
    bool        _linear;
};

int
main()
{
    lm::Core core(400, 400, "Nyan");

    core.push<Nyan>();
    core.start();
}