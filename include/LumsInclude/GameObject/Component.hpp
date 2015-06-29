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

#include <unordered_map>
#include <LumsInclude/Common.hpp>
#include <LumsInclude/Singleton.hpp>
#include <LumsInclude/Binary/BValue.hpp>
 
/**
 * This macro is used to flag a component.
 * You should ALWAYS use this macro in a class used as a component
 */
#ifndef LUMS_CONCAT_
# define LUMS_CONCAT_(a, b)		a ## b
#endif
#ifndef LUMS_CONCAT
# define LUMS_CONCAT(a, b)		LUMS_CONCAT_(a, b)
#endif

#define LUMS_COMPONENT										public:											\
 																size_t id() { return _id; }					\
 																static void setId(size_t id) { _id = id; }	\
 															private:										\
 																static size_t _id;

#define LUMS_REGISTER_COMPONENT(Class, Name) 				size_t Class::_id = 0u;													\
 															LUMS_CONCAT(static lm::internal::RegisterComponent<Class> _reg_, __COUNTER__) (Name)
#define LUMS_BIND_SETTER(ClassName, Name, Method)			LUMS_CONCAT(static lm::internal::BindSetterComponent _bindSetter_, __COUNTER__) (ClassName, Name, reinterpret_cast<void (lm::Component::*)(const lm::BValue&)>(Method))
#define LUMS_BIND_MESSAGE(ClassName, Name, Method)			LUMS_CONCAT(static lm::internal::BindMessageComponent _bindMessage_, __COUNTER__) (ClassName, Name, reinterpret_cast<void (lm::Component::*)()>(Method))

namespace lm
{
	class Component;

	class ComponentFactory : public Singleton<ComponentFactory>
	{
	public:
		Component*
		create(const char* str)
		{
			return create(sym(str));
		}

		Component*
		create(size_t id)
		{
			return _ctors[id]();
		}

		template <typename T>
		void
		reg(const char* str)
		{
			_ctors[sym(str)] = &construct<T>;
		}

	private:
		template <typename T>
		static Component*
		construct()
		{
			return new T;
		}

		std::unordered_map<size_t, Component*(*)()>	_ctors;
	};

	class ComponentBindings : public Singleton<ComponentBindings>
	{
	public:
		void
		bindSetter(const char* className, const char* name, void (Component::*method)(const BValue&))
		{
			_bindings[sym(className)].setters[sym(name)] = method;
		}

		void
		bindMessage(const char* className, const char* name, void (Component::*method)())
		{
			_bindings[sym(className)].messages[sym(name)] = method;
		}

		void
		(Component::*getSetter(size_t id, const char* name))(const BValue&)
		{
			return _bindings[id].setters[sym(name)];
		}

		void
		(Component::*getMessage(size_t id, const char* name))()
		{
			return _bindings[id].messages[sym(name)];
		}

		void
		(Component::*getMessage(size_t id, size_t name))()
		{
			return _bindings[id].messages[name];
		}


	private:
		struct Binding
		{
			std::unordered_map<size_t, void (Component::*)(const BValue&)> setters;
			std::unordered_map<size_t, void (Component::*)()> messages;
		};

		std::unordered_map<size_t, Binding>	_bindings;
	};

	namespace internal
	{
		template <typename T>
		struct RegisterComponent
		{
			RegisterComponent(const char* name)
			{
				ComponentFactory::instance().reg<T>(name);
				T::setId(sym(name));
			}
		};

		struct BindSetterComponent
		{
			BindSetterComponent(const char* className, const char* name, void (Component::*method)(const BValue&))
			{
				ComponentBindings::instance().bindSetter(className, name, method);
			}
		};

		struct BindMessageComponent
		{
			BindMessageComponent(const char* className, const char* name, void (Component::*method)())
			{
				ComponentBindings::instance().bindMessage(className, name, method);
			}
		};
	}

	class GameObject;

	/**
	 * @brief A class that defines behavior and attributes for a GameObject
	 */

	class Component
	{
	public:
		/**
		 * Component ctor
		 */
		Component();
		
		virtual size_t 	id() = 0;

		void			loadBinary(const BObject& object);

		template <typename... Ts>
		void
		recvMessage(GameObject& go, size_t id, Ts... params)
		{
			auto cb = ComponentBindings::instance().getMessage(this->id(), id);
			if (!cb)
				return;
			auto ccb = reinterpret_cast<void (Component::*)(GameObject&, Ts...)>(cb);
			(this->*ccb)(go, std::forward<Ts>(params)...);
		}

		/**
		 * Pure virtual dtor
		 */
		virtual ~Component() = 0;
	};
}

#endif
