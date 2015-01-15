#ifndef LUMS_WINDOW_H
#define LUMS_WINDOW_H

#include <Lums/Event.h>
#include <queue>

namespace lm
{
    class Window
    {
    public:
        Window(int w, int h, const char* name = "");
        
        void
        pushEvent(Event& event)
        {
        	_events.push(event);
        }

        void
        pollEvent(Event& event)
        {
        	extractEvent(event, false);
        }

        void
        waitEvent(Event& event)
        {
        	extractEvent(event, true);
        }

        void    pumpEvent();
        void    swap();
        
        ~Window();

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