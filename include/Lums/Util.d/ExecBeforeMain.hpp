/* ************************************************************************** */
/*                                                                            */
/*    Util/ExecBeforeMain.hpp                        oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_UTIL_EXEC_BEFORE_MAIN_HPP
#define LUMS_UTIL_EXEC_BEFORE_MAIN_HPP

#include <Lums/Util.d/Macros.hpp>

#ifdef EXEC_BEFORE_MAIN
# undef EXEC_BEFORE_MAIN
#endif

#define EXEC_BEFORE_MAIN    static void LUMS_CONCAT(lums_before_main, __LINE__)();  \
                            static ::lm::ExecBeforeMain LUMS_CONCAT(lums_before_main_obj, __LINE__) \
                            (LUMS_CONCAT(lums_before_main, __LINE__)); \
                            static void LUMS_CONCAT(lums_before_main, __LINE__)()

namespace lm
{
    struct ExecBeforeMain {
        ExecBeforeMain(void(*ptr)()) {
            ptr();
        }
    };
}

#endif
