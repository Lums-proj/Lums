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
#include <vector>
#include <Lums/Sound.hpp>
#include <Lums/OperatingSystem.hpp>

using namespace lm;

Sound::Sound(const std::string& name)
: _file(0)
, _format(0)
, _sampleRate(0)
, _read(0)
{
	loadFile(name);
}

void
Sound::play(float x, float y, float z)
{

	if (!_file)
	{
		std::cerr << "Nothing to play !" << std::endl;
		return ;
	}
	ALuint	buffers[2];
	ALuint	source;
	alGenSources(1, &source);
	alSource3f(source, AL_POSITION, x, y, z);
	alGenBuffers(2, buffers);
	readOGG(buffers[0], 44100);
	readOGG(buffers[1], 44100);
	alSourceQueueBuffers(source, 2, buffers);
	alSourcePlay(source);

	ALint nbProcessed;
	ALint status;
	do
	{
	    alGetSourcei(source, AL_BUFFERS_PROCESSED, &nbProcessed);
	    for (ALint i = 0; i < nbProcessed; ++i)
	    {
	        ALuint buffer;
	        alSourceUnqueueBuffers(source, 1, &buffer);
	        readOGG(buffer, 44100);
	        if (_read)
	        	alSourceQueueBuffers(source, 1, &buffer);
	    }

	    alGetSourcei(source, AL_SOURCE_STATE, &status);
	}
	while (status == AL_PLAYING);

	ALint  nbQueued;
	ALuint buffer;

	alGetSourcei(source, AL_BUFFERS_QUEUED, &nbQueued);
	for (ALint i = 0; i < nbQueued; ++i)
	    alSourceUnqueueBuffers(source, 1, &buffer);
	alSourcei(source, AL_BUFFER, 0);

	alDeleteBuffers(2, buffers);
	alDeleteSources(1, &source);
	ov_pcm_seek(&_stream, 0);
}

void
Sound::loadFile(const std::string name, bool resource)
{
	typedef void (Sound::*sndptr_t)(std::string, bool);
    static const std::map<std::string, sndptr_t> extFuncs = {
    	{"ogg", &Sound::loadFileOGG}
    };

    std::string ext = name.substr(name.find_last_of('.') + 1);

    if (extFuncs.find(ext) != extFuncs.end())
        (this->*(extFuncs.at(ext)))(name, resource);
}

void
Sound::loadFileOGG(const std::string name, bool resource)
{
	std::string	path = resource ? resourcePath() + '/' + name : name;

    _file = fopen(path.c_str(), "rb");
    if (!_file)
    {
    	std::cerr << "File not found !" << std::endl;
        return;
    }
	if (ov_open(_file, &_stream, NULL, 0) < 0)
	{
    	std::cerr << "File not found !" << std::endl;
        return;
    }
    vorbis_info* infos = ov_info(&_stream, -1);
    _format = infos->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    _sampleRate = infos->rate;
}

void
Sound::readOGG(ALuint buffer, ALsizei nbSamples)
{
    std::vector<ALshort> samples(nbSamples);

    ALsizei totalRead  = 0;
    ALsizei totalSize  = nbSamples * sizeof(ALshort);
    char*   samplesPtr = reinterpret_cast<char*>(&samples[0]);

    while (totalRead < totalSize)
    {
        _read = ov_read(&_stream, samplesPtr + totalRead, totalSize - totalRead, 0, 2, 1, NULL);
        if (_read > 0)
            totalRead += _read;
        else
            break;
    }
    if (totalRead > 0)
        alBufferData(buffer, _format, &samples[0], totalRead, _sampleRate);
}

Sound::~Sound()
{

}