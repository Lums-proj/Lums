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

#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vorbis/vorbisfile.h>
#include <LumsInclude/Math/vector.hpp>

#define BUFFER_SIZE 40960

namespace lm
{

    namespace Audio
    {
        void    init();
    }

    class Sound
    {
    public:

        void                 setPath(const std::string name, bool resource = true);
        void                 load();
        bool                 loaded();
        void                 unload();
        virtual void         play(Vector3f pos = {0.f, 0.f, 0.f}) = 0;
        virtual void         pause() = 0;
        virtual void         stop() = 0;
        virtual              ~Sound() { unload(); }

    protected:

        void                loadFileOGG();
        void                 setVolumeLimits(ALuint* source, ALfloat* maxGain, ALfloat* minGain);
        float               _volume;
        FILE*               _file;
        OggVorbis_File      _stream;
        ALenum              _format;
        ALsizei             _sampleRate;
        std::string         _path;
    };
}

#endif