/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    TestAngle.cpp                                  oooooo       oooooo      */
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

describe(Angle)
{
    it ("must create a null Angle")
    {
        assert_equal(Angle(), 0_deg);
    }
    
    it ("must ensure equality")
    {
        assert_equal(2.26_deg, 2.26_deg);
        assert_equal(90_deg, 0.25_turn);
        assert_not_equal(25_deg, 25.01_deg);
        assert_not_equal(42_rad, 30_deg);
    }
    
    it ("must handle clamping")
    {
        assert_equal(0_deg, 360_deg);
        assert_equal(-30_deg, 330_deg);
    }
    
    it ("must ensure ordering")
    {
        assert_less(20_deg, 40_deg);
        assert_more(35_deg, 25_deg);
        assert_less_equal(20_deg, 20_deg);
        assert_more_equal(40_deg, 40_deg);
    }
    
    it ("must handle add")
    {
        assert_equal(20_deg + 10_deg, 30_deg);
        assert_equal(80_deg + 300_deg, 20_deg);
    }
    
    it ("must handle substract")
    {
        assert_equal(20_deg - 5_deg, 15_deg);
    }
    
    it ("must handle multiply")
    {
        assert_equal(45_deg * 2, 90_deg);
        assert_equal(200_deg * 2, 40_deg);
    }
    
    it ("must handle divide")
    {
        assert_equal(180_deg / 2, 90_deg);
        assert_equal(1_deg / 4, 0.25_deg);
    }
}