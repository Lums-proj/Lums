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
        static Script   load(const std::string& file, bool resource = true);

        ~Script();

    private:
        void*           _proc;
    };
}

#endif
