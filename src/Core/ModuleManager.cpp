/* ************************************************************************** */
/*                                                                            */
/*    Core/ModuleManager.cpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#include <Lums/Core.d/ModuleManager.hpp>
#include <Lums/Core.d/Module.hpp>

using namespace lm;

void
ModuleManager::addModule(Module* module)
{
    _modules[module->name()] = module;
}

Module*
ModuleManager::module(const char* name) const
{
    if (_modules.find(name) == _modules.end())
        return nullptr;
    return _modules.at(name);
}

void
ModuleManager::load()
{
    for (auto& module : _modules)
        module.second->load();
}

ModuleManager&
ModuleManager::instance()
{
    static ModuleManager moduleManager;

    return moduleManager;
}

/* Private */

ModuleManager::ModuleManager()
{

}
