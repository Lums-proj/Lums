/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Common.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_COMMON_HPP
#define LUMS_COMMON_HPP

#if defined(WIN32) || defined(WIN64)
# define constexpr
#else
# define MODERN_CPP
#endif

#endif