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
        void    PushEvent(Event& event);
        void    PollEvent(Event& event);
        void    WaitEvent(Event& event);
        void    PumpEvent();
        void    Swap();
        ~Window();
    private:
        void                ExtractEvent(Event& event, bool block);

        void*               _windowHandle;
        void*               _openGlHandle;
        std::queue<Event>   _events;
    };
}

#endif