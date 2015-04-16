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

#include <Lums/Lums.hpp>

class Hello : public lm::GameState
{
public:
    Hello()
    : _x(0)
    , _y(0)
    {
        _music.loadFile("music.ogg", lm::Sound::Type::Music);
        _jump.loadFile("jump.ogg", lm::Sound::Type::FX);
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
        _sprite.pos = {50, 50};
        _script.loadFile("hello.mrb");
        _script.run();
        _script.call("hi");
        _frame = 0;
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
        lm::SpriteBatch sb;

        va.push(0, 0, 1, 0, 0);
        va.push(200, 0, 0, 1, 0);
        va.push(200, 200, 0, 0, 1);
        va.push(0, 200, 1, 1, 0);
        va.draw(GL_QUADS);
        sb.begin();
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
                sb.draw(_sprite);
        }
        sb.end();
        _font.printf(0, 50, "Hello, World! %d", _frame);
        _font.printf(0, 120, "x: %f", _x);
        _font.printf(0, 140, "y: %f", _y);
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
                _sprite.flip.x = true;
            else if (event.key == lm::Key::Right)
                _sprite.flip.x = false;
            else if (event.key == lm::Key::Up)
                _sprite.flip.y = true;
            else if (event.key == lm::Key::Down)
                _sprite.flip.y = false;
        }
        if (event.type == lm::Event::Type::LeftStick)
        {
            _x = event.gamepad.stick.x;
            _y = event.gamepad.stick.y;
        }
    }

private:
    lm::Font                _font;
    lm::Image               _mario;
    lm::Sprite              _sprite;
    lm::Script              _script;
    lm::Sound               _music;
    lm::Sound               _jump;
    int         _frame;
    float       _x;
    float       _y;
};

int
main()
{
    lm::Core core(200, 200, "Hello !");

    core.push<Hello>();
    core.start();
    return 0;
}
