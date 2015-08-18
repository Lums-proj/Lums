/* ************************************************************************** */
/*                                                                            */
/*    Core/EntryPoint.cpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#include <Lums/Core.d/EntryPoint.hpp>

static lm::EntryPoint _entryPoint = nullptr;

void
lm::setEntryPoint(lm::EntryPoint entry)
{
    _entryPoint = entry;
}

lm::EntryPoint
lm::entryPoint()
{
    return _entryPoint;
}
