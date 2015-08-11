#include <Lums/Math>
#include "xtest.hpp"

XTEST("vector default construction") {
    lm::Vector2i v;
    XASSERT_EQ(v.x, 0, "x member init");
    XASSERT_EQ(v.y, 0, "y member init");
}
