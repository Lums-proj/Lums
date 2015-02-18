/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SoundManager.hpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SOUND_MANAGER_HPP
#define LUMS_SOUND_MANAGER_HPP

#include <vector>
#include <list>
#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

namespace lm
{

    class Sound;

    enum class SoundState;

    enum class SoundManagerState
    {
        Used = 0,
        Free
    };

    struct Sfx
    {
        Sound*         sound;
        ALuint         source;
        SoundState     state;
    };

    class SoundManager
    {
    public:

        SoundManager();
        static SoundManager&    get();

        void        addSound(Sound* s);
        void        pauseSound(Sound& s);
        void        stopSound(Sound& s);

        void        playMusic();
        void        addMusic(Sound* s);
        void        pauseMusic();
        void        stopMusic();

        ~SoundManager();

    private:

        void        openContext();
        void        getDevices();
        void        setDevice(ALCchar* name);
        void        run();
        void        manageSounds();

        Sfx                            _music;
        std::list<Sfx>                 _sounds;
        ALCdevice*                     _currentDevice;
        ALCcontext*                    _currentContext;
        SoundManagerState              _state;
        std::vector<std::string>       _devices;
        static SoundManager*           _singleton;
    };
}

#endif