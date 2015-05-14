#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vorbis/vorbisfile.h>
#include <mutex>
#include <condition_variable>
#include <LumsInclude/Math/Vector.hpp>


#define BUFFER_SIZE     32768
#define NB_BUFFERS      3

namespace lm
{
    class Music
    {
    public:
        Music();
        void    load(const std::string& name, bool resource = true);
        void    play(lm::Vector3f pos = {0.f, 0.f, 0.f});
        void    pause();
        void    stop();
        ~Music();

    private:
        void    loadOGG(const std::string& name, bool resource);
        void    bufferizeOGG(ALuint& buffer);
        void    readOGG(lm::Vector3f pos);

        ALenum                          _format;
        ALsizei                         _sampleRate;
        ALsizei                         _read;
        FILE*                           _file;
        OggVorbis_File                  _stream;
        std::mutex                      _run_mutex;
        bool                            _run;
        bool                            _ended;
    };
}

#endif