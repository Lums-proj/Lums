/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Script.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SCRIPT_HPP
#define LUMS_SCRIPT_HPP

#include <string>
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>

namespace lm
{
    class Script
    {
    public:
        Script();
        Script(const Script& rhs) = delete;
        Script(Script&& rhs);

        void            loadFile(const std::string& file, bool resource = true);
        void            run();

        template <typename... Args> mrb_value
        call(const char* str, Args... args)
        {
            return mrb_funcall(_mrb, mrb_top_self(_mrb), str, sizeof...(args), args...);
        }

        static Script   load(const std::string& file, bool resource = true);

        ~Script();

    private:
        static mrb_state*   _mrb;
        RProc*              _proc;
    };
}

#endif
