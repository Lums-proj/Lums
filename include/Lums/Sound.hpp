/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sound.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SOUND_HPP
#define LUMS_SOUND_HPP

#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include <vorbis/vorbisfile.h>
#include <Lums/SoundManager.hpp>

#define BUFFER_SIZE   32768

namespace lm
{

    enum class SoundState
    {
        Pending,
        Playing,
        Paused,
        Finished
    };

    enum class SoundType
    {
        Null,
        FX,
        Music
    };

    class Sound
    {
    public:

        Sound();
        void         loadFile(const std::string name, SoundType type, bool resource = true);
        void         play(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void         pause();
        void         stop();
        ALuint       playSound();
        bool         operator==(const Sound& rhs) const;
        bool         operator!=(const Sound& rhs) const;
        ~Sound();

    private:
        ALuint       playMusic();
        ALuint       playFX();
        void         playStream(ALuint source);
        void         loadFileOGG(const std::string name, bool resource);
        void         readOGG(ALuint& Buffer, ALsizei NbSamples);

        FILE*                   _file;
        ALenum                  _format;
        ALsizei                 _sampleRate;
        ALsizei                 _read;
        OggVorbis_File          _stream;
        SoundType               _type;
        SoundState              _state;
        float                   _x;
        float                   _y;
        float                   _z;
        bool                    _run;
        size_t                  _id;
        static size_t           _nbs;
        std::mutex              _mtx;
        std::condition_variable _cv;
        static SoundManager*    _soundManager;
    };
  
}

#endif