/* ************************************************************************** */
/*                                                                            */
/*    Core/Module.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_CORE_MODULE_HPP
#define LUMS_CORE_MODULE_HPP

#include <vector>

namespace lm
{
    class Module
    {
    public:
        using InitFunction = bool (*)();

        Module(const Module&) = delete;
        Module& operator=(const Module&) = delete;

        const char*     name() const { return _name; }
        bool            loaded() const { return _loaded; }
        void            require(const char* module);
        void            load();
        static Module&  create(const char* name, InitFunction initFunc = nullptr);

    private:
        Module(const char* name, InitFunction initFunc);

        const char*                 _name;
        bool                        _loaded;
        std::vector<const char*>    _requiredModules;
        InitFunction                _initFunc;
    };
}

#endif
