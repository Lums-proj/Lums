/* ************************************************************************** */
/*                                                                            */
/*    Core/Module.cpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#include <iostream>
#include <Lums/Core.d/Module.hpp>
#include <Lums/Core.d/ModuleManager.hpp>
#include <Lums/Util.d/Log.hpp>

using namespace lm;

void
Module::require(const char* name)
{
    _requiredModules.push_back(name);
}

void
Module::load()
{
    if (_loaded)
        return;
    for (auto dep : _requiredModules)
    {
        Module* required = ModuleManager::instance().module(dep);
        if (!required)
            die("Module not found: ", dep);
        required->load();
    }
    if (_initFunc)
    {
        if (!_initFunc())
            die("Module ", _name, " initialization failed");
    }
    _loaded = true;
    logMessage("Module ", _name, " was initialized");
}

Module&
Module::create(const char* name, InitFunction initFunc)
{
    Module* module = new Module(name, initFunc);
    lm::ModuleManager::instance().addModule(module);
    return *module;
}

/* Private */

Module::Module(const char* name, InitFunction initFunc)
: _name(name)
, _loaded(false)
, _initFunc(initFunc)
{

}

