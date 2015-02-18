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
        FX,
        Music
    };

    class Sound
    {
    public:

        Sound(const std::string& name, SoundType type);
        void           play(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void           pause();
        void           stop();
        ALuint         playSound();
        void           readSound();
        bool            operator==(Sound& rhs);
        bool            operator!=(Sound& rhs);
        ~Sound();

    private:
        ALuint       playMusic();
        ALuint       playFX();
        void         playStream(ALuint source);
        void         loadFile(const std::string name, bool resource = true);
        void         loadFileOGG(const std::string name, bool resource = true);
        void         readOGG(ALuint& Buffer, ALsizei NbSamples);

        FILE*           _file;
        ALenum          _format;
        ALsizei         _sampleRate;
        ALsizei         _read;
        OggVorbis_File  _stream;
        SoundType       _type;
        SoundState      _state;
        float           _x;
        float           _y;
        float           _z;
        bool            _run;
        size_t          _id;
        static size_t   _nbs;
        std::mutex      _mtx;
        std::condition_variable _cv;
    };
  
}

#endif