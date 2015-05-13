/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Singleton.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SINGLETON_HPP
#define LUMS_SINGLETON_HPP

namespace lm
{
	template <typename T>
	struct Singleton
	{
		static T&
		get()
		{
			static T t;
			return t;
		}
	};
}

#endif
