#include <Lums/Math>
#include "xtest.hpp"
#include <cstdio>

XTEST("vector default construction") {
    lm::Vector2i v;
    XASSERT_EQ(v.x, 0, "x member init");
    XASSERT_EQ(v.y, 0, "y member init");
}

XTEST("vector param construction") {
    lm::Vector4i v(1, 8, 4, 6);
    XASSERT_EQ(v.x, 1, "x member init");
    XASSERT_EQ(v.y, 8, "y member init");
    XASSERT_EQ(v.z, 4, "z member init");
    XASSERT_EQ(v.w, 6, "w member init");
}

XTEST("vector param incomplete construction") {
    lm::Vector4i v(1, 8);
    XASSERT_EQ(v.x, 1, "x member init");
    XASSERT_EQ(v.y, 8, "y member init");
    XASSERT_EQ(v.z, 0, "z member init");
    XASSERT_EQ(v.w, 0, "w member init");
}

XTEST("vector param vector construction") {
    lm::Vector3i v(lm::Vector2i(1, 2), 3);
    XASSERT_EQ(v.x, 1, "x member init");
    XASSERT_EQ(v.y, 2, "y member init");
    XASSERT_EQ(v.z, 3, "z member init");
}
