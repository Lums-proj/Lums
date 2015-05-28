/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Component.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_COMPONENT_HPP
#define LUMS_COMPONENT_HPP

#include <cstring>

#define LUMS_COMPONENT public: virtual size_t classId() const \
					   { static int dummy;                    \
					   	return reinterpret_cast<size_t>(&dummy);}

namespace lm
{
	class Component
	{
	public:
		LUMS_COMPONENT

		using method = void(Component::*)();

		Component();
		
		template <typename T>
		void
		bind(int slot, T function) const
		{
			bind(slot, reinterpret_cast<Component::method>(function));
		}

		void				bind(int slot, Component::method function) const;
		Component::method	handle(int slot) const;
		bool				respondTo(int slot) const;
		virtual ~Component() = 0;
	};
}

#endif
