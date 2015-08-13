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

XTEST("vector downcast") {
    lm::Vector4i v(1, 2, 3, 4);
    lm::Vector2i vv(v);

    XASSERT_EQ(vv.x, 1, "x member");
    XASSERT_EQ(vv.y, 2, "y member");
}

XTEST("vector upcast") {
    lm::Vector2i k(1, 5);
    lm::Vector4i v1(k);
    lm::Vector4i v2(0, k);
    lm::Vector4i v3(k, k);

    XASSERT_EQ(v1.x, 1, "x1 member init");
    XASSERT_EQ(v1.y, 5, "y1 member init");
    XASSERT_EQ(v1.z, 0, "z1 member init");
    XASSERT_EQ(v1.w, 0, "w1 member init");

    XASSERT_EQ(v2.x, 0, "x2 member init");
    XASSERT_EQ(v2.y, 1, "y2 member init");
    XASSERT_EQ(v2.z, 5, "z2 member init");
    XASSERT_EQ(v2.w, 0, "w2 member init");

    XASSERT_EQ(v3.x, 1, "x3 member init");
    XASSERT_EQ(v3.y, 5, "y3 member init");
    XASSERT_EQ(v3.z, 1, "z3 member init");
    XASSERT_EQ(v3.w, 5, "w3 member init");
}

XTEST("vector addition") {
    lm::Vector4i v(lm::Vector4i(1, 4) + lm::Vector4i(lm::Vector3i(3, 7, 8)));
    XASSERT_EQ(v.x, 4, "x member");
    XASSERT_EQ(v.y, 11, "y member");
    XASSERT_EQ(v.z, 8, "z member");
    XASSERT_EQ(v.w, 0, "w member");
}

XTEST("vector scalar addition") {
    lm::Vector2i v(1, 5);
    v += 7;
    XASSERT_EQ(v.x, 8, "x member");
    XASSERT_EQ(v.y, 12, "y member");
}

XTEST("vector substraction") {
    lm::Vector2i v{5, 3};
    v -= {4, 8};
    XASSERT_EQ(v.x, 1, "x member");
    XASSERT_EQ(v.y, -5, "y member");
}

XTEST("vector scalar substraction") {
    lm::Vector2i v(1, 5);
    v -= 7;
    XASSERT_EQ(v.x, -6, "x member");
    XASSERT_EQ(v.y, -2, "y member");
}

XTEST("vector product") {
    lm::Vector2i v{5, 3};
    v *= {4, 8};
    XASSERT_EQ(v.x, 20, "x member");
    XASSERT_EQ(v.y, 24, "y member");
}

XTEST("vector scalar product") {
    lm::Vector2i v(1, 5);
    v *= 7;
    XASSERT_EQ(v.x, 7, "x member");
    XASSERT_EQ(v.y, 35, "y member");
}

XTEST("vector quotient") {
    lm::Vector2i v{20, 9};
    v /= {5, 3};
    XASSERT_EQ(v.x, 4, "x member");
    XASSERT_EQ(v.y, 3, "y member");
}

XTEST("vector scalar quotient") {
    lm::Vector2i v(30, 15);
    v /= 5;
    XASSERT_EQ(v.x, 6, "x member");
    XASSERT_EQ(v.y, 3, "y member");
}

XTEST("vector unary plus") {
    lm::Vector2i v(1, 2);
    XASSERT_EQ((+v).x, 1, "x member");
    XASSERT_EQ((+v).y, 2, "y member");
}

XTEST("vector unary minus") {
    lm::Vector2i v(1, 2);
    XASSERT_EQ((-v).x, -1, "x member");
    XASSERT_EQ((-v).y, -2, "y member");
}

XTEST("vector equality") {
    lm::Vector2i v(1, 2);
    lm::Vector2i vv(v);
    XASSERT_EQ(v, vv, "vector equal");
}

XTEST("vector inequality") {
    lm::Vector2i v(1, 2);
    lm::Vector2i vv(-v);
    XASSERT_NEQ(v, vv, "vector not equal");
}

XTEST("null vector") {
    XASSERT_TRUE(lm::null(lm::Vector2i()), "null vector");
    XASSERT_FALSE(lm::null(lm::Vector2i(1, 2)), "not null vector");
}
