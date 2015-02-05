/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Window.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_WINDOW_HPP
#define LUMS_WINDOW_HPP

#include <queue>
#include <Lums/Event.hpp>
#include <Lums/ExportDll.hpp>

namespace lm
{
    /**
    * This class defines a Window.
    */
    class Window
    {
    public:
        /**
        * Create a new window.
        * @param w The width of the window.
        * @param h The height of the window.
        * @param name The name of the window.
        */
        LUMS_EXPORTED Window(int w, int h, const char* name = "");
        
        /**
        * Push an event on the internal event stack.
        * @event The event to be pushed.
        */
        void
        pushEvent(Event& event)
        {
        	_events.push(event);
        }

        /**
        * Poll an event from the event stack.
        * If the event stack is empty, the event type will
        * be set to Event::Type::None
        * @param event A reference to an event, which will be filled
        * with data.
        */
        void
        pollEvent(Event& event)
        {
        	extractEvent(event, false);
        }

        /**
        * Wait for an event from the event stack.
        * If the event stack is empty, this method will block and wait.
        * @param event A reference to an event, which will be filled
        * with data.
        */
        void
        waitEvent(Event& event)
        {
        	extractEvent(event, true);
        }

        /**
        * Pump event from the underlying implementation to the event stack.
        */
        LUMS_EXPORTED void    pumpEvent();

        /**
        * Swap the current buffer with the backbuffer.
        */
        LUMS_EXPORTED void    swap();
        
        /**
        * Destructor
        */
        LUMS_EXPORTED ~Window();

    private:

        void
        extractEvent(Event& event, bool block)
        {
        	while (true)
    		{
		        pumpEvent();
		        if (!_events.empty())
		        {
		            event = _events.front();
		            _events.pop();
		            return;
		        }
		        else if (!block)
		        {
		            event.type = Event::Type::None;
		            return;
		        }
		    }
		}

        void*               _windowHandle;
        void*               _openGlHandle;
        std::queue<Event>   _events;
    };
}

#endif