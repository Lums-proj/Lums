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
#include <Lums/SoundManager.hpp>

using namespace lm;

SoundManager::SoundManager()
: _currentDevice(0)
, _currentContext(0)
{
    _singleton = this;
    openContext();
}

SoundManager&
SoundManager::get()
{
    return *_singleton;
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
        std::cerr << "Unable to active context." << std::endl;
}

SoundManager::~SoundManager()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(_currentContext);
    alcCloseDevice(_currentDevice);
}

SoundManager* SoundManager::_singleton = 0;