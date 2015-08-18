/* ************************************************************************** */
/*                                                                            */
/*    Window/Window.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#include <Lums/Window.d/Window.hpp>
#include <Lums/Util.d/ExecBeforeMain.hpp>
#include <Lums/Core.d/Module.hpp>

#ifdef __APPLE__
# include "MacOSX/WindowImpl.hpp"
#endif

using namespace lm;

static bool
initWindowModule()
{
#ifdef __APPLE__
    initApplication();
#endif
    return true;
}

EXEC_BEFORE_MAIN {
    Module& window = Module::create("window", initWindowModule);
    window.require("core");
}

Window::Window(unsigned width, unsigned height, const char* name)
{
    _geometry = {{0, 0}, {float(width), float(height)}};
    _impl = new WindowImpl(this, width, height, name);
}

Window::~Window()
{
    delete _impl;
}
