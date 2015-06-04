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

#include <cstring>

namespace lm
{
	/**
	 * Return a hash from a string.
	 * This function can be used to compute compile-time hashes.
	 * @param str The string to be hashed.
	 * @return A hash
	 */
	inline constexpr std::size_t
	sym(const char* str)
	{
		return *str ? (sym(str + 1) * 103) + ((*str << 4) ^ 63) * 3 + 0x8cf4 : 804577;
	}
}

#endif