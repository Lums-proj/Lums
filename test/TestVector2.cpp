/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    TestVector2.cpp                              &------&     &------&      */
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

describe(Vector2)
{
    it ("must create a null Vector2")
    {
        assert_equal(Vector2i().x, 0);
        assert_equal(Vector2i().y, 0);
    }
    
    it ("must create Vector2 with parameters")
    {
        Vector2i v(5, -3);

        assert_equal(v.x, 5);
        assert_equal(v.y, -3);
    }
    
    it ("must support set")
    {
        Vector2i v;

        v.set(8, 42);
        assert_equal(v.x, 8);
        assert_equal(v.y, 42);
    }
    
    it ("must support add")
    {
        Vector2i v = Vector2i(1, 1) + Vector2i(2, 3);

        assert_equal(v.x, 3);
        assert_equal(v.y, 4);
    }
    
    it ("must support substract")
    {
        Vector2i v = Vector2i(1, 1) - Vector2i(2, 3);
        
        assert_equal(v.x, -1);
        assert_equal(v.y, -2);
    }
    
    it ("must support multiply")
    {
        Vector2i v = Vector2i(5, 10) * 2;

        assert_equal(v.x, 10);
        assert_equal(v.y, 20);
    }
    
    it ("must support divide")
    {
        Vector2i v = Vector2i(5, 10) / 2;

        assert_equal(v.x, 2);
        assert_equal(v.y, 5);
    }
    
    it ("must support null")
    {
        assert_if(Vector2i().null());
        assert_unless(Vector2i(0, 1).null());
    }
    
    it ("must support length")
    {
        assert_equal(Vector2i(3, -4).length(), 5);
    }
    
    it ("must support unit and normalize")
    {
        assert_max_diff(Vector2d(7, 349).unit().length(), 1.0, 0.001);
    }
}