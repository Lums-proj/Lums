/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    TestVecto2.cpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include "NanoTest.hpp"
#include <Lums/Lums.hpp>

using namespace		lm;

describe(Vector2)
{
    it ("must create a null Vector2")
    {
        assert_equal(Vector2f().x, 0);
        assert_equal(Vector2f().y, 0);
    }
    
    it ("must create Vector2 with parameters")
    {
        Vector2f v(2, -4);

        assert_equal(v.x, 2);
        assert_equal(v.y, -4);
    }
    
    it ("must support add")
    {
        Vector2f v = Vector2f(1, 1) + Vector2f(3, 3);

        assert_equal(v.x, 4);
        assert_equal(v.y, 4);
    }
    
    it ("must support substract")
    {
        Vector2f v = Vector2f(1, 1) - Vector2f(3, 9);
        
        assert_equal(v.x, -2);
        assert_equal(v.y, -8);
    }
    
    it ("must support multiply")
    {
        Vector2f v = Vector2f(2, 4) * 2;

        assert_equal(v.x, 4);
        assert_equal(v.y, 8);
    }
    
    it ("must support divide")
    {
        Vector2f v = Vector2f(16, 8) / 2;

        assert_equal(v.x, 8);
        assert_equal(v.y, 4);
    }
    
    it ("must support null")
    {
        assert_if(null(Vector2f()));
        assert_unless(null(Vector2f(0, 1)));
    }
    
    it ("must support length")
    {
        assert_equal(length(Vector2f(3, -4)), 5);
    }
    
    it ("must support unit and normalize")
    {
        assert_max_diff(length(normal(Vector2f(7, 349))), 1.0, 0.001);
    }
}