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

static float    globalVolume = 1.f;

void
Sfx::setGlobalVolume(float volume)
{
    globalVolume = volume;
}

Sfx::Sfx()
: _sources(0)
{
    file = nullptr;
    volume = 1.0f;
}

Sfx::Sfx(Sfx&& rhs)
: Sound(std::forward<Sound>(rhs))
{
    _sources = rhs._sources;
}

Sfx&
Sfx::operator=(Sfx&& rhs)
{
    *(static_cast<Sound*>(this)) = std::forward<Sound>(rhs);
    _sources = rhs._sources;
    return *this;
}

void
Sfx::play(Vector3f pos)
{
    ALuint  source;
    ALuint  buffer;

    clearSources();
    _sources.push_back(source);
    alGenBuffers(1, &buffer);
    alGenSources(1, &(_sources.back()));
    alSource3f(_sources.back(), AL_POSITION, pos.x, pos.y, pos.z);
    alSourcef(_sources.back(), AL_GAIN, volume * globalVolume);
    std::vector<char>   bufferData;
    char array[BUFFER_SIZE];
    ALsizei bytes;
    do
    {
        bytes = ov_read(&stream, array, BUFFER_SIZE, 0, 2, 1, nullptr);
        bufferData.insert(bufferData.end(), array, array + bytes);
    } while (bytes > 0);
    alBufferData(buffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), sampleRate);
    alSourcei(_sources.back(), AL_BUFFER, buffer);
    ov_pcm_seek(&stream, 0);
    alSourcePlay(_sources.back());
}

void
Sfx::pause()
{

}

void
Sfx::stop()
{
    for (auto it = _sources.begin(); it != _sources.end(); ++it)
    {
        alSourceStop(*it);
        alDeleteSources(1, &(*it));
        // TODO : free the buffer
    }
    _sources.clear();
}

void
Sfx::setVolume(float newVolume)
{
    ALfloat maxGain;
    ALfloat minGain;

    if (_sources.size())
        setVolumeLimits(&(_sources.back()), &maxGain, &minGain);
    else
        setVolumeLimits(nullptr, &maxGain, &minGain);
    if (newVolume >= minGain && newVolume <= maxGain)
        volume = newVolume;
    for(auto it = _sources.begin(); it != _sources.end(); ++it)
        alSourcef(*it, AL_GAIN, volume * globalVolume);
}

void
Sfx::clearSources()
{
    ALint   sourceState;
    
    for (auto it = _sources.begin(); it != _sources.end(); ++it)
    {
        alGetSourcei(*it, AL_SOURCE_STATE, &sourceState);
        if (sourceState != AL_PLAYING)
        {
            alSourceStop(*it);
            alDeleteSources(1, &(*it));
        }
    }
}

Sfx::~Sfx()
{

}