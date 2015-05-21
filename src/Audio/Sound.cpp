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
    _path = resource ? resourcePath() + name : name;
}

void
Sound::load()
{
    typedef void (Sound::*sndptr_t)();
    static const std::map<std::string, sndptr_t> extFuncs = {
        {"ogg", &Sound::loadFileOGG}
    };

    std::string ext = _path.substr(_path.find_last_of('.') + 1);

    if (extFuncs.find(ext) != extFuncs.end())
        (this->*(extFuncs.at(ext)))();
}

void
Sound::loadFileOGG()
{
    _file = fopen(_path.c_str(), "rb");
    if (!_file)
    {
        std::cerr << "File not found: " << _path << std::endl;
        return;
    }
    if (ov_open_callbacks(_file, &_stream, 0, 0, OV_CALLBACKS_DEFAULT) < 0)
    {
        fclose(_file);
        _file = 0;
        std::cerr << "Stream error: " << _path << std::endl;
        return;
    }
    vorbis_info* infos = ov_info(&_stream, -1);
    _format = (infos->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    _sampleRate = infos->rate;
}