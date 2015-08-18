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

#include <functional>
#include <thread>
#include <vector>
#include <LumsInclude/Audio/Music.hpp>

using namespace lm;

Music::Music()
: _state(Music::Stopped)
{
    file = nullptr;
    volume = 1.0f;
}

Music::Music(Music&& rhs)
: Sound(std::forward<Sound>(rhs))
{
    _source = rhs._source;
    _state = rhs._state;
}


Music&
Music::operator=(Music&& rhs)
{
    *(static_cast<Sound*>(this)) = std::forward<Sound>(rhs);
    _source = rhs._source;
    _state = rhs._state;
    return *this;
}

void
Music::play(Vector3f pos)
{
    std::function<void (void)> func;

    switch (_state)
    {
        case Music::Paused:
            func = [this]() { alSourcePlay(_source); };
            state(Music::Playing, func);
            break;
        case Music::Stopped:
        {
            _state = Music::Playing;
            std::thread t1([this](Vector3f pos)
            {
                streamOGG(pos);
            }, pos);
            t1.detach();
            break;
        }
        default:
            break;
    }
}

void
Music::pause()
{
    if (_state == Music::Playing)
        state(Music::Paused, [this]() { alSourcePause(_source); });
}

void
Music::stop()
{
    if (_state == Music::Stopped)
        return;
    state(Music::Stopped, [this]() { alSourceStop(_source); });
}

void
Music::state(Music::State state, std::function<void (void)> func)
{
    std::lock_guard<std::mutex> lock(_mtx);
    _state = state;
    func();
}

void
Music::setVolume(float newVolume)
{

    std::lock_guard<std::mutex> lock(_mtx);
    ALfloat maxGain;
    ALfloat minGain;

    setVolumeLimits(&_source, &maxGain, &minGain);
    if (newVolume >= minGain && newVolume <= maxGain)
        volume = newVolume;
    alSourcef(_source, AL_GAIN, volume);
}

void
Music::streamOGG(Vector3f pos)
{
    std::chrono::milliseconds dura(400);
    ALuint  buffers[NB_BUFFERS];
    ALint   nbProcessed;
    ALint   sourceState;
    int     index = 0;

    _mtx.lock();
    alGenSources(1, &_source);
    alGenBuffers(NB_BUFFERS, buffers);
    alSource3f(_source, AL_POSITION, pos.x, pos.y, pos.z);
    alSourcef(_source, AL_GAIN, volume);
    for (int i = 0; i < NB_BUFFERS; ++i)
        bufferizeOGG(buffers[i]);
    alSourceQueueBuffers(_source, NB_BUFFERS, buffers);
    alSourcePlay(_source);
    while (1)
    {
        alGetSourcei(_source, AL_BUFFERS_PROCESSED, &nbProcessed);
        if (nbProcessed)
        {
            alSourceUnqueueBuffers(_source, 1, &buffers[index]);
            bufferizeOGG(buffers[index]);
            alSourceQueueBuffers(_source, 1, &buffers[index]);
            index = (index == 2) ? 0 : index++;
        }
        alGetSourcei(_source, AL_SOURCE_STATE, &sourceState);
        if (sourceState == AL_STOPPED)
            break;
        _mtx.unlock();
        std::this_thread::sleep_for(dura); // Will be removed
        _mtx.lock();
    }
    alSourceUnqueueBuffers(_source, NB_BUFFERS, buffers);
    alDeleteBuffers(NB_BUFFERS, buffers);
    alDeleteSources(1, &_source);
    ov_pcm_seek(&stream, 0);
    _mtx.unlock();
}

void
Music::bufferizeOGG(ALuint& buffer)
{
    std::vector<ALshort> samples(sampleRate);
    ALsizei read;
    ALsizei totalRead  = 0;
    ALsizei totalSize  = sampleRate * sizeof(ALshort);
    char*   samplesPtr = reinterpret_cast<char*>(&samples[0]);

    while (totalRead < totalSize)
    {
        read = ov_read(&stream, samplesPtr + totalRead, totalSize - totalRead, 0, 2, 1, nullptr);
        if (read > 0)
            totalRead += read;
        else if (read == 0)
            ov_pcm_seek(&stream, 0);
         else    
            break;
    }
    if (totalRead > 0)
        alBufferData(buffer, format, &samples[0], totalRead, sampleRate);
}

Music::~Music()
{

}