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
#include <LumsInclude/Graphics/Key.hpp>
#include <LumsInclude/Singleton.hpp>

namespace lm
{
    /**
     * @brief A struct describing an event
     */
    struct Event
    {
        /**
         * An enum describing the event type
         */
        enum class Type
        {
            None = 0,
            GamepadConnected,
            GamepadDisconnected,
            KeyDown,
            KeyUp,
            ButtonDown,
            ButtonUp,
            LeftMouseDown,
            LeftMouseUp,
            RightMouseDown,
            RightMouseUp,
            MouseMove,
            LeftStick,
            RightStick,
            LeftTrigger,
            RightTrigger,
        };

        /**
         * The event type
         */
        Event::Type type;
        
        /**
         * A tagged union for the event data
         */
        union
        {
            /**
             * The event key
             */
            Key     key;

            /**
             * A struct describing the gamepad state
             */
            struct
            {
                /**
                 * The gamepad id
                 */
                uintptr_t id;

                /**
                 * A tagged union describing the gamepad state
                 */
                union
                {
                    /**
                     * The button id
                     */
                    int     button;

                    /**
                     * The normalized trigger value
                     */
                    float   trigger;

                    /**
                     * A struct describing a stick
                     */
                    struct
                    {
                        /**
                         * The normalized stick direction on the x axis
                         */
                        float x;

                        /**
                         * The normalized stick direction on the y axis
                         */
                        float y;
                    } stick;
                };
            } gamepad;

            /**
             * A struct describing the mouse
             */
            struct
            {
                /**
                 * The cursor x position
                 */
                int x;

                /**
                 * The cursor y position
                 */
                int y;
            } mouse;
        };
    };
}

#endif