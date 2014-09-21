/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    CoreCurses.cpp                               &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/CoreCurses.h>

using namespace lm;

CoreCurses::CoreCurses()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    meta(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    ESCDELAY = 25;
    for (int i = 0; i < 64; i++)
        init_pair(i + 1, i % 8, i / 8);
}

CoreCurses::~CoreCurses()
{
    endwin();
}