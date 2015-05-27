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
#include <LumsInclude/GameObject/Component.hpp>

namespace lm
{
	class GameObject
	{
	public:
		GameObject();

		template <typename... Ts>
		void
		send(int slot, Ts... params)
		{
			std::function<void (Ts...)> = func;
			for (auto& c : _components)
			{
				void* h = c->handle(slot);

			}
		}
		
		~GameObject();

	private:
		std::vector<Component*>	_components;
	};
}

#endif
