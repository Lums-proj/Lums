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
#include <unordered_set>
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
		void			update();

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
			return getComponent<void>(id) != nullptr;
		}

		template <typename T>
		T*
		getComponent(const char* name)
		{
			return getComponent<T>(sym(name));
		}

		template <typename T>
		T*
		getComponent(size_t id)
		{
			for (auto c : _components)
			{
				if (c->id() == id)
					return static_cast<T*>(c);
			}
			return nullptr;
		}

		void
		removeComponent(const char* name)
		{
			removeComponent(sym(name));
		}

		void
		removeComponent(size_t id)
		{
			for (int i = 0 ; i < _components.size(); ++i)
			{
				if (_components[i]->id() == id)
				{
					delete _components[i];
					_components.erase(_components.begin() + i);
					return;
				}
			}
		}		

        bool    hasTag(const char* tag) const { return hasTag(lm::sym(tag)); }
        bool    hasTag(size_t tag) const { return _tags.find(tag) != _tags.end(); }
        void    setTag(const char* tag) { setTag(sym(tag)); }
        void    setTag(size_t tag) { _tags.insert(tag); }
        void    clearTag(const char* tag) { clearTag(sym(tag)); }
        void    clearTag(size_t tag) { _tags.erase(tag); }

		~GameObject();

		Vector3f position;
		Vector3f rotation;
		Vector3f scale;

	private:
		std::vector<Component*>	    _components;
        std::unordered_set<size_t>  _tags;
	};
}

#endif
