/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    TestVector3.cpp                                oooooo       oooooo      */
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

describe (Vector3)
{
    it ("must create a null Vector3")
    {
        assert_equal(Vector3f().x, 0);
        assert_equal(Vector3f().y, 0);
        assert_equal(Vector3f().z, 0);
    }
    
    it ("must create Vector3 with parameters")
    {
        Vector3f v(5, -3, 9);
        
        assert_equal(v.x, 5);
        assert_equal(v.y, -3);
        assert_equal(v.z, 9);
    }
    
    it ("must support add")
    {
        Vector3f v = Vector3f(1, 1, 1) + Vector3f(2, 3, 4);
        
        assert_equal(v.x, 3);
        assert_equal(v.y, 4);
        assert_equal(v.z, 5);
    }
    
    it ("must support substract")
    {
        Vector3f v = Vector3f(1, 1, 1) - Vector3f(2, 3, 4);
        
        assert_equal(v.x, -1);
        assert_equal(v.y, -2);
        assert_equal(v.z, -3);
    }
    
    it ("must support multiply")
    {
        Vector3f v = Vector3f(5, 10, 15) * 2;
        
        assert_equal(v.x, 10);
        assert_equal(v.y, 20);
        assert_equal(v.z, 30);
    }
    
    it ("must support divide")
    {
        Vector3f v = Vector3f(5, 10, 15) / 2;
        
        assert_equal(v.x, 2.5);
        assert_equal(v.y, 5);
        assert_equal(v.z, 7.5);
    }
    
    it ("must support null")
    {
        assert_if(null(Vector3f()));
        assert_unless(null(Vector3f(0, 0, 1)));
    }
    
    it ("must support length")
    {
        assert_equal(length(Vector3f(2, -3, -6)), 7);
    }
    
    it ("must support unit and normalize")
    {
        assert_max_diff(length(normal(Vector3f(7, 349, -1024))), 1.0, 0.001);
    }
}
