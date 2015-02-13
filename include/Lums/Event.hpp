/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Event.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_EVENT_HPP
#define LUMS_EVENT_HPP

#include <cstdint>
#include <Lums/Key.hpp>

namespace lm
{
    struct Event
    {
        enum class Type
        {
            None = 0,
            GamepadConnected,
            GamepadDisconnected,
            KeyDown,
            KeyUp,
            ButtonDown,
            ButtonUp
        };

        Event::Type type;
        
        union
        {
            Key     key;
            struct
            {
                uintptr_t   id;
                union
                {
                    int     button;
                };
            }
            gamepad;
        };
    };
}

#endif