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
	class GameObject
	{
	public:
		void	addComponent(Component*);

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
					auto func = reinterpret_cast<void (Component::*)(Ts...)>(h);
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
			_components.push_back(std::unique_ptr<Component>(new T(std::forward<Ts>(params)...)));
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

	private:
		std::vector<std::unique_ptr<Component>>	_components;
	};
}

#endif
