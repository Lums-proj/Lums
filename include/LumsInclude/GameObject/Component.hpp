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

#include <LumsInclude/Common.hpp>


/**
 * This macro is used to flag a component.
 * You should ALWAYS use this macro in a class used as a component
 */
#define LUMS_COMPONENT public: size_t static Id()                  \
					   { static int dummy   ;                      \
					   	return reinterpret_cast<size_t>(&dummy); } \
					   virtual size_t classId() const			   \
					   { return Id(); }



namespace lm
{
	/**
	 * @brief A class that defines behavior and attributes for a GameObject
	 */
	class Component
	{
	public:
		LUMS_COMPONENT

		/**
		 * An alias
		 */
		using method = void (Component::*)();

		/**
		 * Component ctor
		 */
		Component();
		
		/**
		 * Bind a method to a slot
		 * @tparam T Used for type erasure
		 * @param slot The destination slot
		 * @param function The method to bind
		 */
		template <typename T>
		void
		bind(int slot, T function) const
		{
			bind(slot, reinterpret_cast<Component::method>(function));
		}

		/**
		 * Bind a method to a slot
		 * @tparam T Used for type erasure
		 * @param slot A string representing a slot - it will be hashed
		 * (at compile time if possible)
		 * @param function The method to bind
		 */
		template <typename T>
		void
		bind(const char* slot, T function) const
		{
			bind(sym(slot), function);
		}

		/**
		 * A no-op, catch-all implementation of update
		 * @tparam Ts Used for type erasure
		 * @param params Any parameters
		 */
		template <typename... Ts>
		void
		update(Ts... params)
		{

		}

		/**
		 * A no-op, catch-all implementation of render
		 * @tparam Ts Used for type erasure
		 * @param params Any parameters
		 */
		template <typename... Ts>
		void
		render(Ts... params)
		{
			
		}

		/**
		 * A no-op, catch-all implementation of handleEvent
		 * @tparam Ts Used for type erasure
		 * @param params Any parameters
		 */
		template <typename... Ts>
		void
		handleEvent(Ts... params)
		{
		
		}

		/**
		 * Bind a method to a slot
		 * @param slot The destination slot
		 * @param function The method to bind
		 */
		void				bind(int slot, Component::method function) const;

		/**
		 * Get an untyped handle to a slot
		 * @param slot The target slot
		 * @return An untyped handle to the slot
		 */
		Component::method	handle(int slot) const;

		/**
		 * Check if the component react to a slot
		 * @param slot The slot
		 * @return True if the component react, false otherwise
		 */
		bool				respondTo(int slot) const;

		/**
		 * Pure virtual dtor
		 */
		virtual ~Component() = 0;
	};
}

#endif
