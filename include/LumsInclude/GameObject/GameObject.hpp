/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameObject.hpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAME_OBJECT_HPP
#define LUMS_GAME_OBJECT_HPP

#include <vector>
#include <functional>
#include <type_traits>
#include <LumsInclude/GameObject/Component.hpp>

namespace lm
{
	/**
	 * @brief A composite class representing any object in a game.
	 * 
	 * This class should be used as a CRTP.
	 * @tparam Derived The derived class, for CRTP
	 * @tparam ComponentType The derived component type
	 */
	template <typename Derived, typename ComponentType>
	class GameObject
	{
	public:
		/**
		 * Send a message to every components this GameObject holds
		 * @tparam Ts Used for type erasure
		 * @param slot The destination slot
		 * @param params Parameters
		 * @return True if the message was received by at least one component
		 */
		template <typename... Ts>
		bool
		send(int slot, Ts... params)
		{
			bool b = false;
			for (auto& c : _components)
			{
				auto h = c->handle(slot);
				if (h)
				{
					b = true;
					auto func = reinterpret_cast<void (ComponentType::*)(Ts...)>(h);
					auto cp = c.get();
					(cp->*func)(params...);
				}
			}
			return b;
		}

		/**
		 * Send a message to every components this GameObject holds
		 * @tparam Ts Used for type erasure
		 * @param slot The destination slot - it will be hashed at compile time
		 * @param params Parameters
		 * @return True if the message was received by at least one component
		 */
		template <typename... Ts>
		bool
		send(const char* slot, Ts... params)
		{
			return send(sym(slot), params...);
		}

		/**
		 * Get a response from a component
		 * @tparam The return type
		 * @param slot The slot to listen to.
		 * @return A pointer to data, or nullptr.
		 */
		template <typename T>
		T*
		recv(int slot)
		{
			for (auto& c : _components)
			{
				auto h = c->handle(slot);
				if (h)
				{
					auto func = reinterpret_cast<T* (ComponentType::*)()>(h);
					auto cp = c.get();
					return (cp->*func)();
				}
			}
			return nullptr;
		}

		/**
		 * Get a response from a component
		 * @tparam The return type
		 * @param slot The slot to listen to - it will be hashed at compile time if possible
		 * @return A pointer to data, or nullptr.
		 */
		template <typename T>
		T*
		recv(const char* slot)
		{
			return recv<T>(sym(slot));
		}

		/**
		 * Attach a new component to the game object
		 * It's undefined behavior to attach multiples instances of
		 * the same component.
		 * @tparam T The component to create
		 * @tparam Ts Constructor parameter types
		 * @param params Constructor parameters
		 */
		template <typename T, typename... Ts>
		void
		attach(Ts... params)
		{
			_components.push_back(std::unique_ptr<ComponentType>(new T(std::forward<Ts>(params)...)));
		}

		/**
		 * Check wether a component is attached to this object.
		 * @tparam T The component type to check
		 * @return True if the object holds a component of type T
		 */
		template <typename T>
		bool
		composed() const
		{
			return get<T>() != nullptr;
		}

		/**
		 * Detach the component of type T attached to this object.
		 * If there is no such component, do nothing.
		 * @tparam T The component type
		 */
		template <typename T>
		void
		detach()
		{
			for (size_t i = 0; i < _components.size(); ++i)
			{
				if (_components[i]->classId() == T::Id())
				{
					_components.erase(_components.begin() + i);
					return;
				}
			}
		}

		/**
		 * Get a pointer to the component of type T attached to this object.
		 * If there is no such component, return nullptr.
		 * @tparam T The component type.
		 * @return A pointer to the component, or nullptr.
		 */
		template <typename T>
		T*
		get() const
		{
			for (auto& c : _components)
			{
				if (c->classId() == T::Id())
					return static_cast<T*>(c.get());
			}
			return nullptr;
		}

		/**
		 * Iterate over each component, and call update on them.
		 * @tparam Ts Parameter types
		 * @param params Parameters
		 */
		template <typename... Ts>
		void
		update(Ts... params)
		{
			for (auto& c : _components)
				c->update(*static_cast<Derived*>(this), std::forward<Ts>(params)...);
		}

		/**
		 * Iterate over each component, and call render on them.
		 * @tparam Ts Parameter types
		 * @param params Parameters
		 */
		template <typename... Ts>
		void
		render(Ts... params)
		{
			for (auto& c : _components)
				c->render(*static_cast<Derived*>(this), std::forward<Ts>(params)...);
		}

		/**
		 * Iterate over each component, and call handleEvent on them.
		 * @tparam Ts Parameter types
		 * @param params Parameters
		 */
		template <typename... Ts>
		void
		handleEvent(Ts... params)
		{
			for (auto& c : _components)
				c->handleEvent(*static_cast<Derived*>(this), std::forward<Ts>(params)...);
		}

	private:
		std::vector<std::unique_ptr<ComponentType>>	_components;
	};
}

#endif
