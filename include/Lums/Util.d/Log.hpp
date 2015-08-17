/* ************************************************************************** */
/*                                                                            */
/*    Util/Log.hpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_UTIL_LOG_HPP
#define LUMS_UTIL_LOG_HPP

#include <ctime>
#include <cstdlib>
#include <iostream>

#include <Lums/Util.d/Macros.hpp>

#define LM_LINE     __FILE__ ":" LM_STRINGIFY(__LINE__)
#define LM_LOG(...) ::lm::logMessage(LM_LINE " ", __VA_ARGS__)
#define LM_DIE(...) ::lm::die(LM_LINE " ", __VA_ARGS__)

namespace lm
{
    namespace priv
    {
        inline void
        logMessageImpl()
        {
            std::cout << std::endl;
        }

        template <typename T, typename... Ts>
        inline void
        logMessageImpl(const T& head, const Ts&... params)
        {
            std::cout << head;
            logMessageImpl(params...);
        }
    }

    template <typename... Ts>
    inline void
    logMessage(const Ts&... params)
    {
        char timeBuf[256];
        time_t now;
        tm* localNow;

        time(&now);
        localNow = localtime(&now);
        strftime(timeBuf, 256, "[%d %B %Y %T] ", localNow);
        std::cout << timeBuf;
        priv::logMessageImpl(params...);
    }

    template <typename... Ts>
    inline void
    die(const Ts&... params)
    {
        logMessage(params...);
        exit(1);
    }
}

#endif
