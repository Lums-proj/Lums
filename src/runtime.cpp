#include <Lums/Util>
#include <Lums/Core>

using namespace lm;

int
main(int argc, char* argv[])
{
    EntryPoint entry;

    ModuleManager::instance().load();
    entry = entryPoint();
    if (entry)
        return entry(argc, argv);
    else
    {
        logMessage("No entry point");
        return 0;
    }
}
