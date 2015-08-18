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

#ifndef LUMS_WINDOW_WINDOW_HPP
#define LUMS_WINDOW_WINDOW_HPP

#include <Lums/Math.d/Rect.hpp>

namespace lm
{
    class WindowImpl;
    class Window
    {
    public:
        Window(unsigned width, unsigned height, const char* name = "");
        
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        ~Window();

    private:
        WindowImpl*     _impl;
        lm::Rect2f      _geometry;
    };
}

#endif
