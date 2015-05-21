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
        _volumeMusic = 1.f;
        _volumeSfx = 1.f;
        lm::MusicProvider::instance().set(0).setPath("music.ogg");
        lm::SfxProvider::instance().set(0).setPath("jump.ogg");
    }

    void
    load()
    {
        auto& music = lm::MusicProvider::instance().get(0);
        music.play();
    }

    void
    update()
    {

    }

    void
    handleEvent(const lm::Event& event)
    {
        auto& music = lm::MusicProvider::instance().get(0);
        auto& sfx = lm::SfxProvider::instance().get(0);

        if (event.type == lm::Event::Type::KeyDown)
        {
            switch (event.key)
            {
                case lm::Key::Space:
                    sfx.play();
                    break;
                case lm::Key::Q:
                    sfx.stop();
                    break;
                case lm::Key::P:
                    music.pause();
                    break;
                case lm::Key::S:
                    music.stop();
                    break;
                case lm::Key::L:
                    music.play();
                    break;
                case lm::Key::Up:
                    _volumeMusic += 0.1f;
                    music.setVolume(_volumeMusic);
                    break;
                case lm::Key::Down:
                    _volumeMusic -= 0.1f;
                    music.setVolume(_volumeMusic);
                    break;
                case lm::Key::Right:
                    _volumeSfx += 0.1f;
                    sfx.setVolume(_volumeSfx);
                    break;
                case lm::Key::Left:
                    _volumeSfx -= 0.1f;
                    sfx.setVolume(_volumeSfx);
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
    float       _volumeMusic;
    float       _volumeSfx;
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