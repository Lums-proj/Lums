#include <Lums/Util.d/ExecBeforeMain.hpp>
#include <Lums/Core.d/Module.hpp>

using namespace lm;

EXEC_BEFORE_MAIN {
    Module::create("core");
}
