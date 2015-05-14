#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <LumsInclude/OperatingSystem.hpp>
#include <LumsInclude/Audio/Music.hpp>
#include <LumsInclude/Audio/SoundManager.hpp>

using namespace lm;

static SoundManager* soundManager = nullptr;

Music::Music()
: _format(0)
, _sampleRate(0)
, _read(0)
, _file(0)
, _run(false)
, _ended(true)
{
    if (!soundManager)  
        soundManager = new SoundManager;
}

void
Music::load(const std::string& name, bool resource)
{
    std::string path = resource ? resourcePath() + name : name;
    _file = fopen(path.c_str(), "rb");
    if (!_file)
    {
        std::cerr << "File not found !" << std::endl;
        return;
    }
    loadOGG(name, resource);
}

void
Music::loadOGG(const std::string& name, bool resource)
{
    if (ov_open_callbacks(_file, &_stream, 0, 0, OV_CALLBACKS_DEFAULT) < 0)
    {
        fclose(_file);
        _file = 0;
        std::cerr << "File not found !" << std::endl;
        return;
    }
    vorbis_info* infos = ov_info(&_stream, -1);
    _format = infos->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    _sampleRate = infos->rate;
}

void
Music::bufferizeOGG(ALuint& buffer)
{
    std::vector<ALshort> samples(_sampleRate);
    ALsizei totalRead  = 0;
    ALsizei totalSize  = _sampleRate * sizeof(ALshort);
    char*   samplesPtr = reinterpret_cast<char*>(&samples[0]);

    while (totalRead < totalSize)
    {
        _read = ov_read(&_stream, samplesPtr + totalRead, totalSize - totalRead, 0, 2, 1, nullptr);
        if (_read > 0)
            totalRead += _read;
        else    
            break;
    }
    if (totalRead > 0)
        alBufferData(buffer, _format, &samples[0], totalRead, _sampleRate);
}

void
Music::readOGG(Vector3f pos)
{
    ALuint  source;
    ALuint  buffers[NB_BUFFERS];
    ALint   nbProcessed;
    int     index = 0;

    alGenSources(1, &source);
    alGenBuffers(NB_BUFFERS, buffers);
    alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
    for (int i = 0; i < NB_BUFFERS; ++i)
        bufferizeOGG(buffers[i]);
    alSourceQueueBuffers(source, NB_BUFFERS, buffers);
    alSourcePlay(source);
    std::chrono::milliseconds dur(400);
    _run_mutex.lock();
    _run = true;
    _ended = false;
    while (_run)
    {
        _run_mutex.unlock();
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &nbProcessed);
        if (!nbProcessed)
        {
            std::this_thread::sleep_for(dur);
            continue;
        }
        alSourceUnqueueBuffers(source, 1, &buffers[index]);
        bufferizeOGG(buffers[index]);
        if (!_read)
        {
            ov_pcm_seek(&_stream, 0);
            bufferizeOGG(buffers[index]);
        }
        alSourceQueueBuffers(source, 1, &buffers[index]);
        index = (index == 2) ? 0 : index++;
        _run_mutex.lock();
    }
    for (int i = 0; i < NB_BUFFERS; ++i)
       alSourceUnqueueBuffers(source, 1, &buffers[i]);
    alDeleteBuffers(NB_BUFFERS, buffers);
    alDeleteSources(1, &source);
    ov_pcm_seek(&_stream, 0);
    _ended = true;
    _run_mutex.unlock();
}

void
Music::play(lm::Vector3f pos)
{
    _run_mutex.lock();
    bool ended = _ended;
    _run_mutex.unlock();    
    if (!ended)
        return;
    std::thread    t1([this](Vector3f pos) { readOGG(pos); }, pos);
    t1.detach();
}

void
Music::pause()
{
     std::lock_guard<std::mutex> guard(_run_mutex);
}

void
Music::stop()
{
    std::lock_guard<std::mutex> guard(_run_mutex);
    _run = false;
}

Music::~Music()
{
    if (!_file)
        return;
    std::lock_guard<std::mutex> guard(_run_mutex);
    _run = false;
    ov_clear(&_stream);
    fclose(_file);
}