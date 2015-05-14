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
		instance()
		{
			static T t;
			return t;
		}
		
	protected:
		Singleton() = default;
		Singleton(const Singleton<T>&) = delete;
		Singleton<T>& operator=(const Singleton<T>&) = delete;
	};
}

#endif
