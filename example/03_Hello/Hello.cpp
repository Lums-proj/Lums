/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Hello.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <Lums/Lums.hpp>
#include <Lums/Script.hpp>
#include <Lums/SoundManager.hpp>
#include <Lums/Sound.hpp>
#include <iostream>

class Hello : public lm::GameState
{
public:
    Hello()
    {
        _music.loadFile("music.ogg", lm::SoundType::Music);
        _jump.loadFile("jump.ogg", lm::SoundType::FX);
        _music.play();
    }

    void
    load()
    {
        glMatrixMode(GL_PROJECTION);
        glOrtho(0, 200, 200, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
#if WIN32
        _font.load("Arial.ttf", 16);
#else
        _font.load("Arial Black.ttf", 16);
#endif
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        _mario.loadFile("mario.png");
        _mario.atlas(16);
        _mario.linear(false);
        _sprite.setImage(_mario);
        _sprite.setAnimation(1, 3, 10);
        _sprite.setScale(3);
        _script.loadFile("hello.mrb");
        _script.run();
        _script.call("hi");
        _frame = 0;
        _arr.push(0, 0, 1, 0.5, 1);
    }

    void
    update()
    {
        _frame++;
        _sprite.update();
    }

    void
    render() const
    {
        lm::VertexArrayc<4> va;

        va.push(0, 0, 1, 0, 0);
        va.push(200, 0, 0, 1, 0);
        va.push(200, 200, 0, 0, 1);
        va.push(0, 200, 1, 1, 0);
        va.draw(GL_QUADS);
        _font.printf(0, 50, "Hello, World! %d", _frame);
        _font.printf(0, 120, "x: %f", _x);
        _font.printf(0, 140, "y: %f", _y);
        _sprite.draw(92, 92);
    }

    void
    handleEvent(const lm::Event& event)
    {
        if (event.type == lm::Event::Type::KeyDown)
        {
            _jump.play();
            if (event.key == lm::Key::Escape)
                lm::Core::get().stop();
            else if (event.key == lm::Key::Left)
                _sprite.flipX(true);
            else if (event.key == lm::Key::Right)
                _sprite.flipX(false);
            else if (event.key == lm::Key::Up)
                _sprite.flipY(true);
            else if (event.key == lm::Key::Down)
                _sprite.flipY(false);
        }
        if (event.type == lm::Event::Type::LeftStick)
        {
            _x = event.gamepad.stick.x;
            _y = event.gamepad.stick.y;
        }
    }

private:
    lm::Font    _font;
    lm::Image   _mario;
    lm::Sprite  _sprite;
    lm::Script  _script;
    lm::Sound   _music;
    lm::Sound   _jump;
    lm::VertexArrayc<256>  _arr;
    int         _frame;
    float       _x;
    float       _y;
};

int
main()
{
    lm::Core core(200, 200, "Hello !");
    lm::SoundManager    SoundManager;

    core.push<Hello>();
    core.start();
    return 0;
}
