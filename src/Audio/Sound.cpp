/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sound.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <LumsInclude/OperatingSystem.hpp>
#include <LumsInclude/Audio/Sound.hpp>

using namespace lm;


void
Audio::init()
{
    ALCdevice*  device = alcOpenDevice(nullptr);
     if (!device)
    {
         std::cerr << "Unable to open device" << std::endl;
        return;
    }
    ALCcontext* context = alcCreateContext(device, nullptr);
    if (!context)
    {
        std::cerr << "Unable to create context." << std::endl;
        return;
    }
    if (!alcMakeContextCurrent(context))
    {
        std::cerr << "Unable to enable context." << std::endl;
        return;
    }
}

void
Sound::setPath(const std::string name, bool resource)
{
    path = resource ? resourcePath() + name : name;
}

void
Sound::load()
{
    typedef void (Sound::*sndptr_t)();
    static const std::map<std::string, sndptr_t> extFuncs = {
        {"ogg", &Sound::loadFileOGG}
    };

    std::string ext = path.substr(path.find_last_of('.') + 1);

    if (extFuncs.find(ext) != extFuncs.end())
        (this->*(extFuncs.at(ext)))();
}

bool
Sound::loaded()
{   
    return (file != nullptr);
}

void
Sound::unload()
{
    if (!file)
        return;
    ov_clear(&stream);
    fclose(file);
    file = nullptr;
}

void
Sound::loadFileOGG()
{
    file = fopen(path.c_str(), "rb");
    if (!file)
    {
        std::cerr << "File not found: " << path << std::endl;
        return;
    }
    if (ov_open_callbacks(file, &stream, 0, 0, OV_CALLBACKS_DEFAULT) < 0)
    {
        fclose(file);
        file = 0;
        std::cerr << "Stream error: " << path << std::endl;
        return;
    }
    vorbis_info* infos = ov_info(&stream, -1);
    format = (infos->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    sampleRate = infos->rate;
}

void
Sound::setVolumeLimits(ALuint* source, ALfloat* maxGain, ALfloat* minGain)
{
    if (source && alIsSource(*source))
    {
        alGetSourcef(*source, AL_MAX_GAIN, maxGain);
        alGetSourcef(*source, AL_MIN_GAIN, minGain);
        return;    }
    *maxGain = 1.f;
    *minGain = 0.f;
}