/* ************************************************************************** */
/*                                                                            */
/*    Window/MacOSX/WindowImpl.hpp                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_WINDOW_WINDOW_IMPL_MACOSX_HPP
#define LUMS_WINDOW_WINDOW_IMPL_MACOSX_HPP

#ifdef __OBJC__
# import <Cocoa/Cocoa.h>
#else
using NSOpenGLContext = void;
using NSWindow = void;
#endif

namespace lm
{
    class Window;
    class WindowImpl
    {
    public:
        WindowImpl(Window* parent, unsigned width, unsigned height, const char* name = "");

    private:
        Window*             _parent;
        NSOpenGLContext*    _openGl;
        NSWindow*           _window;
    };

    void    initApplication();
}

#endif
