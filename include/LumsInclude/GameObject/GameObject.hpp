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
#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
	class GameObject
	{
	public:
		GameObject();
		Component*		attach(const char* name) { return attach(sym(name)); }
		Component*		attach(size_t id);
		void			detach(const char* name) { detach(sym(name)); }
		void			detach(size_t id);
		void			init();

		template <typename... Ts>
		void
		send(const char* name, Ts... params)
		{
			send(sym(name), std::forward<Ts>(params)...);
		}

		template <typename... Ts>
		void
		send(size_t id, Ts... params)
		{
			for (auto c : _components)
				c->recvMessage(*this, id, std::forward<Ts>(params)...);
		}

		bool
		hasComponent(const char* name)
		{
			return hasComponent(sym(name));
		}

		bool
		hasComponent(size_t id)
		{
			return getComponent(id) != nullptr;
		}

		Component*
		getComponent(const char* name)
		{
			return getComponent(sym(name));
		}

		Component*
		getComponent(size_t id)
		{
			for (auto c : _components)
			{
				if (c->id() == id)
					return c;
			}
			return nullptr;
		}

		~GameObject();

		Vector3f position;
		Vector3f rotation;
		Vector3f scale;

	private:
		std::vector<Component*>	_components;
	};
}

#endif
