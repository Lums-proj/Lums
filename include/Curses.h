/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Curses.h                                     &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_CURSES_H
#define LUMS_CURSES_H

#include <ncurses.h>

namespace lm
{
    inline constexpr int    curseColor(int fg, int bg)
    {
        return 1 + fg + bg * 8;
    }

    inline void             curseSetColor(int fg, int bg)
    {
        color_set(curseColor(fg, bg), NULL);
    }
}

#endif