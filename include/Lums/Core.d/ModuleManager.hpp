/* ************************************************************************** */
/*                                                                            */
/*    Core/ModuleManager.hpp                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_CODE_MODULE_MANAGER_HPP
#define LUMS_CODE_MODULE_MANAGER_HPP

#include <unordered_map>
#include <string>

namespace lm
{
    class Module;
    class ModuleManager
    {
    public:
        ModuleManager(const ModuleManager&) = delete;
        ModuleManager& operator=(const ModuleManager&) = delete;

        Module* module(const char* name) const;

        void    addModule(Module* module);
        void    load();

        static ModuleManager& instance();

    private:
        ModuleManager();

        std::unordered_map<std::string, Module*>    _modules;
    };
}

#endif
