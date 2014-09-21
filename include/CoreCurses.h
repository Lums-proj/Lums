/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    CoreCurses.h                                 &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_CORE_CURSES_H
#define LUMS_CORE_CURSES_H

#include <Lums/Core.h>
#include <ncurses.h>

namespace lm
{
    /**
     * A class representing an ncurses core.
     */
    class CoreCurses;
    class GameStateCurses;
    
    template<>
    struct CoreTraits<CoreCurses>
    {
        typedef int             Event;
        typedef GameStateCurses State;
    };
    
    class CoreCurses : public Core<CoreCurses>
    {
    public:
        /**
         * Create a new ncurses core.
         */
        CoreCurses();
        
        /**
         * Get the win width.
         */
        int     Width()
        {
            return _width;
        }
        
        /**
         * Get the win height.
         */
        int     Height()
        {
            return _height;
        }
        
        /**
         * Poll an event from the event stream.
         * Already called by the main loop.
         * @return True if an event exist.
         */
        bool    PollEvent()
        {
            _event = getch();
            if (_event == KEY_RESIZE)
            {
                _width = COLS;
                _height = LINES;
            }
            return _event != ERR;
        }
        
        void    ClearScreen()
        {
            erase();
        }
        
        void    RefreshScreen()
        {
            refresh();
        }
        
        ~CoreCurses();

    private:
        int                 _width;
        int                 _height;
    };
}

#endif