/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ExportDll.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_EXPORTDLL_HPP
#define LUMS_EXPORTDLL_HPP

#ifdef WIN32
# ifdef EXPORT_DLL
#  define LUMS_EXPORTED __declspec(dllexport)
# else
#  define LUMS_EXPORTED __declspec(dllimport)
# endif
#else
# define LUMS_EXPORTED
#endif

#endif