#ifndef LUMS_EVENT_H
#define LUMS_EVENT_H

#ifdef __APPLE__
# include <Lums/MacOSX/KeyCode.h>
#endif

namespace lm
{
    struct Event
    {
        enum class Type
        {
            None = 0,
            KeyUp,
            KeyDown
        };

        Event::Type type;
        
        union
        {
            Key     key;
        };
    };
}

#endif