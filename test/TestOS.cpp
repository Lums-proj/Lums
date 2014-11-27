/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    TestOS.cpp                                   &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include "NanoTest.h"
#include <Lums/Lums.h>

using namespace		lm;

describe (OperatingSystem)
{
    it ("must provide non-empty resource path")
    {
        assert_not_equal(resourcePath(), "");
    }
}