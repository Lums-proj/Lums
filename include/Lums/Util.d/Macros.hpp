/* ************************************************************************** */
/*                                                                            */
/*    Util/Macros.hpp                                oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*    (c) 2013 - 2015                                                         */
/* ************************************************************************** */

#ifndef LUMS_UTIL_MACROS_HPP
#define LUMS_UTIL_MACROS_HPP

#define LM_CONCAT_(a, b)        a ## b
#define LM_CONCAT(a, b)         LM_CONCAT_(a, b)

#define LM_STRINGIFY_(str)      #str
#define LM_STRINGIFY(str)       LM_STRINGIFY_(str)

#endif
