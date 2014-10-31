/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    TestVector3.cpp                              &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <NanoTest.h>
#include <Lums/Lums.h>

using namespace		lm;

describe (Vector3)
{
    it ("must create a null Vector3")
    {
        assert_equal(Vector3i().x, 0);
        assert_equal(Vector3i().y, 0);
        assert_equal(Vector3i().z, 0);
    }
    
    it ("must create Vector3 with parameters")
    {
        Vector3i v(5, -3, 9);
        
        assert_equal(v.x, 5);
        assert_equal(v.y, -3);
        assert_equal(v.z, 9);
    }
    
    it ("must support set")
    {
        Vector3i v;
        
        v.Set(8, 42, 19);
        assert_equal(v.x, 8);
        assert_equal(v.y, 42);
        assert_equal(v.z, 19);
    }
    
    it ("must support add")
    {
        Vector3i v = Vector3i(1, 1, 1) + Vector3i(2, 3, 4);
        
        assert_equal(v.x, 3);
        assert_equal(v.y, 4);
        assert_equal(v.z, 5);
    }
    
    it ("must support substract")
    {
        Vector3i v = Vector3i(1, 1, 1) - Vector3i(2, 3, 4);
        
        assert_equal(v.x, -1);
        assert_equal(v.y, -2);
        assert_equal(v.z, -3);
    }
    
    it ("must support multiply")
    {
        Vector3i v = Vector3i(5, 10, 15) * 2;
        
        assert_equal(v.x, 10);
        assert_equal(v.y, 20);
        assert_equal(v.z, 30);
    }
    
    it ("must support divide")
    {
        Vector3i v = Vector3i(5, 10, 15) / 2;
        
        assert_equal(v.x, 2);
        assert_equal(v.y, 5);
        assert_equal(v.z, 7);
    }
    
    it ("must support null")
    {
        assert_if(Vector3i().Null());
        assert_unless(Vector3i(0, 0, 1).Null());
    }
    
    it ("must support length")
    {
        assert_equal(Vector3i(2, -3, -6).Length(), 7);
    }
    
    it ("must support unit and normalize")
    {
        assert_max_diff(Vector3d(7, 349, -1024).Unit().Length(), 1.0, 0.001);
    }
}