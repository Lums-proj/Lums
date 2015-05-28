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
#include <LumsInclude/GameObject/Component.hpp>

namespace lm
{
	class GameObject
	{
	public:
		GameObject();

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
		
		~GameObject();

	private:
		std::vector<std::unique_ptr<Component>>	_components;
	};
}

#endif
