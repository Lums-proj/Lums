/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    TestOS.cpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include "NanoTest.hpp"
#include <Lums>

using namespace		lm;

describe (OperatingSystem)
{
    it ("must provide non-empty resource path")
    {
        assert_not_equal(resourcePath(), "");
    }
}