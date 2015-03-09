/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SoundManager.cpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <thread>
#include <chrono>
#include <Lums/Sound.hpp>
#include <Lums/SoundManager.hpp>

using namespace lm;

SoundManager::SoundManager()
: _currentDevice(0)
, _currentContext(0)
, _state(SoundManagerState::Free)
{
    _music.sound = 0;
    _singleton = this;
    openContext();
}

SoundManager&
SoundManager::get()
{
    return *_singleton;
}

void
SoundManager::addSound(Sound* sound)
{
    Sfx     s;
    s.sound = sound;
    s.state = SoundState::Pending;
    s.source = 0;
    std::chrono::milliseconds dura(400);
    while (_state != SoundManagerState::Free)
        std::this_thread::sleep_for(dura);
    _state = SoundManagerState::Used;
    _sounds.push_back(s);
    _state = SoundManagerState::Free;
}

void
SoundManager::pauseSound(Sound& sound)
{
    std::list<Sfx>::iterator it;

    for (it = _sounds.begin(); it != _sounds.end(); ++it)
    {
        Sound*  s = (*it).sound;
        if (sound == *s && (*it).state == SoundState::Playing)
        {
            alSourcePause((*it).source);
            (*it).state = SoundState::Paused;
        }
    }
}

void
SoundManager::stopSound(Sound& sound)
{
    std::list<Sfx>::iterator it;

    for (it = _sounds.begin(); it != _sounds.end(); ++it)
    {
        Sound*  s = (*it).sound;
        if (sound == *s)
        {
            alSourceStop((*it).source);
            (*it).state = SoundState::Finished;
        }
    }
}

void
SoundManager::manageSounds()
{
    std::list<Sfx>::iterator it;    

    for (it = _sounds.begin(); it != _sounds.end(); ++it)
    {
        switch ((*it).state)
        {
            case SoundState::Finished:
            {
                _sounds.erase(it);
                break;
            }
            case SoundState::Pending:
            {
                ALuint  ret = (*it).sound->playSound();
                (*it).state = SoundState::Playing;
                if (ret)
                    (*it).source = ret;
                else
                    _sounds.erase(it);
                break;
            }
            case SoundState::Playing:
            {
                ALint   state;
                alGetSourcei((*it).source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING)
                    (*it).state = SoundState::Finished;
                break;
            }
            default:
                break;
        }
    }
}

void
SoundManager::playMusic()
{
    if (_music.source)
    {
        _music.state = SoundState::Playing;
        alSourcePlay(_music.source);
    }       
}


void
SoundManager::addMusic(Sound* sound)
{
    Sfx     s;
    s.sound = sound;
    s.state = SoundState::Playing;
    s.source = sound->playSound();
    std::chrono::milliseconds dura(400);
    while (_state != SoundManagerState::Free)
        std::this_thread::sleep_for(dura);
    if (_music.sound && *(_music.sound) != *sound)
        _music.sound->stop();
    _state = SoundManagerState::Used;
    _music = s;
    _state = SoundManagerState::Free;
}


void
SoundManager::pauseMusic()
{
    _music.state = SoundState::Paused;
    alSourcePause(_music.source);
}

void
SoundManager::stopMusic()
{
    _music.state = SoundState::Finished;
    alSourceStop(_music.source);
}

void
SoundManager::openContext()
{
    setDevice(NULL);
}

void
SoundManager::getDevices()
{ 
    const ALCchar*  deviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

     _devices.clear();
    if (deviceList)
    {
        size_t  length = std::strlen(deviceList);
        while (length > 0)
        {
            _devices.push_back(deviceList);
            deviceList += length + 1;
        }
    }
}

void
SoundManager::setDevice(ALCchar* name)
{
    ALCdevice*  device = alcOpenDevice(name);

    if (device)
        _currentDevice = device;
    else
    {
        std::cerr << "Unable to open device" << std::endl;
        return;
    }
    _currentContext = alcCreateContext(_currentDevice, NULL);
    if (!_currentContext)
    {
        std::cerr << "Unable to create context." << std::endl;
        return;
    }
    if (!alcMakeContextCurrent(_currentContext))
    {
        std::cerr << "Unable to active context." << std::endl;
        return;
    }
    run();
}

void
SoundManager::run()
{
    std::thread     t1([this]()
        {
            std::chrono::milliseconds dura(20);
            while (1)
            {
                /**
                 * KLUDGE
                 * This should use a condition variable and a mutex.
                 * The expected gain is in the order of 10~20x.
                 */
                _state = SoundManagerState::Used;
                manageSounds();
                _state = SoundManagerState::Free;
                std::this_thread::sleep_for(dura);
            }
        });
    t1.detach();
}

SoundManager::~SoundManager()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(_currentContext);
    alcCloseDevice(_currentDevice);
}

SoundManager* SoundManager::_singleton = 0;