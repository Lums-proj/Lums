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
	template <typename Derived, typename ComponentType>
	class GameObject
	{
	public:
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

		template <typename T, typename... Ts>
		void
		attach(Ts... params)
		{
			_components.push_back(std::unique_ptr<ComponentType>(new T(std::forward<Ts>(params)...)));
		}

		template <typename T>
		bool
		composed() const
		{
			return get<T>() != nullptr;
		}

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

		template <typename... Ts>
		void
		update(Ts... params)
		{
			for (auto& c : _components)
				c->update(*static_cast<Derived*>(this), std::forward<Ts>(params)...);
		}

		template <typename... Ts>
		void
		render(Ts... params)
		{
			for (auto& c : _components)
				c->render(*static_cast<Derived*>(this), std::forward<Ts>(params)...);
		}

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
