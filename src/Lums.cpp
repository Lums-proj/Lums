/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Lums.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <Lums/Lums.hpp>

using namespace lm;

static void
enableCore()
{

}

static void
enableGraphics()
{
    Application::init();
}

static void
enableAudio()
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
internal::_enableSingleModule(Module module)
{
    switch (module)
    {
        case Module::Core:
            enableCore();
            break;
        case Module::Graphics:
            enableGraphics();
            break;
        case Module::Audio:
            enableAudio();
            break;
        case Module::All:
            enableCore();
            enableGraphics();
            enableAudio();
            break;
    }
}