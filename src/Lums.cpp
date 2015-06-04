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

#include <LumsInclude/Lums.hpp>

using namespace lm;

static void
enableCore()
{

}

static void
enableGraphics()
{
    Application::init();
    Freetype::init();
}

static void
enableAudio()
{    
    Audio::init();
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