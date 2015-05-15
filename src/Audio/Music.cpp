/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Music.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <vector>
#include <LumsInclude/Audio/Music.hpp>

using namespace lm;

Music::Music()
{
    _file = 0;
}

void
Music::play(Vector3f pos)
{
    std::thread    t1([this](Vector3f pos)
    {
        streamOGG(pos);
    }, pos);
    t1.detach();
}

void
Music::pause()
{

}

void
Music::stop()
{

}

void
Music::streamOGG(Vector3f pos)
{
    std::chrono::milliseconds dura(400);
    ALuint  buffers[NB_BUFFERS];
    ALint   nbProcessed;
    ALint   status;
    ALuint  source;
    int     index = 0;

    alGenSources(1, &source);
    alGenBuffers(NB_BUFFERS, buffers);
    alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
    for (int i = 0; i < NB_BUFFERS; ++i)
        bufferizeOGG(buffers[i]);
    alSourceQueueBuffers(source, NB_BUFFERS, buffers);
    alSourcePlay(source);
    while (1)
    {
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &nbProcessed);
        if (nbProcessed)
        {
            alSourceUnqueueBuffers(source, 1, &buffers[index]);
            bufferizeOGG(buffers[index]);
            alSourceQueueBuffers(source, 1, &buffers[index]);
            index = (index == 2) ? 0 : index++;
        }
        std::this_thread::sleep_for(dura); // Will be removed
    }
    alSourceUnqueueBuffers(source, NB_BUFFERS, buffers);
    alDeleteBuffers(NB_BUFFERS, buffers);
    alDeleteSources(1, &source);
    ov_pcm_seek(&_stream, 0);
}

void
Music::bufferizeOGG(ALuint& buffer)
{
    std::vector<ALshort> samples(_sampleRate);
    ALsizei read;
    ALsizei totalRead  = 0;
    ALsizei totalSize  = _sampleRate * sizeof(ALshort);
    char*   samplesPtr = reinterpret_cast<char*>(&samples[0]);

    while (totalRead < totalSize)
    {
        read = ov_read(&_stream, samplesPtr + totalRead, totalSize - totalRead, 0, 2, 1, nullptr);
        if (read > 0)
            totalRead += read;
        else if (read == 0)
            ov_pcm_seek(&_stream, 0);
         else    
            break;
    }
    if (totalRead > 0)
        alBufferData(buffer, _format, &samples[0], totalRead, _sampleRate);
}

Music::~Music()
{

}