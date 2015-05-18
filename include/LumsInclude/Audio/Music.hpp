/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Music.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_MUSIC_HPP
#define LUMS_MUSIC_HPP

#include  <mutex>
#include <LumsInclude/Audio/Sound.hpp>

#define NB_BUFFERS  3

namespace lm
{
    class Music : public Sound
    {
    public:

        enum State
        {
            Playing,
            Paused,
            Stopped
        };

        Music();
        void    play(Vector3f pos = {0.f, 0.f, 0.f});
        void    pause();
        void    stop();
        ~Music();
    private:
        void    state(Music::State state, std::function<void (void)> func);
        void    streamOGG(Vector3f pos);
        void    bufferizeOGG(ALuint& buffer);

        ALuint          _source;
        Music::State    _state;
        std::mutex      _mtx;
    };
}

#endif