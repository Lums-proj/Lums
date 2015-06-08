#include <Lums>
#include "Assets.hpp"
#include "Game.hpp"

int
main()
{
    lm::enableModules(lm::Module::All);
    auto& core = lm::Core::instance();
    core.setWindow(new lm::Window(800, 600, "<%= @params[:name] %>"));
    core.push<Game>();
    core.start();
}
