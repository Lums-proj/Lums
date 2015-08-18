/* ************************************************************************** */
/*                                                                            */
/*    Core/EntryPoint.hpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_CORE_ENTRY_POINT_HPP
#define LUMS_CORE_ENTRY_POINT_HPP

namespace lm
{
    using EntryPoint = int (*)(int, char* []);

    void            setEntryPoint(EntryPoint entry);
    EntryPoint      entryPoint();
}

#endif
