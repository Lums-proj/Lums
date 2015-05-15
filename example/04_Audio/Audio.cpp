/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Audio.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums>

class Audio : public lm::GameState
{
public:
    Audio()
    {

    }

    void
    load()
    {
        _music.loadFile("music.ogg");
        _sfx.loadFile("jump.ogg");
        _music.play();
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
            switch (event.key)
            {
                case lm::Key::Space:
                    _sfx.play();
                    break;
                case lm::Key::Q:
                    _sfx.stop();
                    break;
                default:
                    lm::Core::instance().stop();
                    break;
            }
        }
    }

    void
    render()
    {

    }

private:
    lm::Music   _music;
    lm::Sfx     _sfx;
};

int     main()
{
    lm::enableModule(lm::Module::Core);
    lm::enableModule(lm::Module::Audio);
    lm::enableModule(lm::Module::Graphics);
    lm::Core& core = lm::Core::instance();
    core.setWindow(new lm::Window(400, 400, "Audio"));
    core.push<Audio>();
    core.start();
}