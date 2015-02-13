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

namespace lm
{

    class Sound
    {
    public:

        Sound(const std::string& name);
        void    play(float x, float y, float z = 0.0f);
        ~Sound();

    private:

        void    loadFile(const std::string name, bool resource = true);
        void    loadFileOGG(const std::string name, bool resource = true);
        void    readOGG(ALuint Buffer, ALsizei NbSamples);

        FILE*           _file;
        ALenum          _format;
        ALsizei         _sampleRate;
        ALsizei         _read;
        OggVorbis_File  _stream;
    };

}

#endif