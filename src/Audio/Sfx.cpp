/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sfx.cpp                                        oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <LumsInclude/Audio/Sfx.hpp>

using namespace lm;

Sfx::Sfx()
: _sources(0)
{
    _file = 0;
    _volume = 1.0f;
}

void
Sfx::play(Vector3f pos)
{
    ALuint  source;
    ALuint  buffer;

    _sources.push_back(source);
    alGenBuffers(1, &buffer);
    alGenSources(1, &(_sources.back()));
    alSource3f(_sources.back(), AL_POSITION, pos.x, pos.y, pos.z);
    alSourcef(_sources.back(), AL_GAIN, _volume);
    std::vector<char>   bufferData;
    char array[BUFFER_SIZE];
    ALsizei bytes;
    ALint state;
    do
    {
        bytes = ov_read(&_stream, array, BUFFER_SIZE, 0, 2, 1, nullptr);
        bufferData.insert(bufferData.end(), array, array + bytes);
    } while (bytes > 0);
    alBufferData(buffer, _format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), _sampleRate);
    alSourcei(_sources.back(), AL_BUFFER, buffer);
    ov_pcm_seek(&_stream, 0);
    alSourcePlay(_sources.back());
}

void
Sfx::pause()
{

}

void
Sfx::stop()
{
    for(auto it = _sources.begin(); it != _sources.end(); ++it)
    {
        alSourceStop(*it);
        alDeleteSources(1, &(*it));
    }
    _sources.clear();
}

void
Sfx::setVolume(float volume)
{
    if (volume >= 0.f && volume <= 1.0f)
        _volume = volume;
    for(auto it = _sources.begin(); it != _sources.end(); ++it)
        alSourcef(*it, AL_GAIN, volume);
}

Sfx::~Sfx()
{

}