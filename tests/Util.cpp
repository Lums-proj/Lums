#include <Lums/Util>
#include "xtest.hpp"

static int count = 0;

EXEC_BEFORE_MAIN {
    count++;
}

XTEST("exec before main") {
    XASSERT_EQ(count, 1, "increment before main");
}
