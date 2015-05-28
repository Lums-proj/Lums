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

#define LUMS_COMPONENT public: size_t static Id()                  \
					   { static int dummy   ;                      \
					   	return reinterpret_cast<size_t>(&dummy); } \
					   virtual size_t classId() const			   \
					   { return Id(); }



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

		template <typename... Ts>
		void
		update(Ts... params)
		{

		}

		template <typename... Ts>
		void
		render(Ts... params)
		{
			
		}

		template <typename... Ts>
		void
		handleEvent(Ts... params)
		{
		
		}

		void				bind(int slot, Component::method function) const;
		Component::method	handle(int slot) const;
		bool				respondTo(int slot) const;
		virtual ~Component() = 0;
	};
}

#endif
