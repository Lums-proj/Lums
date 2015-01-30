#ifndef LUMS_COMMON_HPP
#define LUMS_COMMON_HPP

#if defined(WIN32) || defined(WIN64)
# define constexpr
#else
# define MODERN_CPP
#endif

#endif