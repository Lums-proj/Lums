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
}

void
Sfx::play(Vector3f pos)
{
    ALuint  source;
    ALuint  buffer;

    _sources.push_back(source);
    alGenBuffers(1, &buffer);
    alGenSources(1, &(_sources.back()));
    alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
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

Sfx::~Sfx()
{

}