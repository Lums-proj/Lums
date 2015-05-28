#include <iostream>
#include <Lums>

class Entity;

class EntityComponent : public lm::Component
{
	LUMS_COMPONENT

public:
	virtual void update(Entity&, const char* str) {};
	virtual void render(Entity&) {};
	virtual void handleEvent(Entity&) {};
};

class Entity : public lm::GameObject<Entity, EntityComponent> {};

class HelloComponent : public EntityComponent
{
	LUMS_COMPONENT

public:
	HelloComponent()
	{
		bind(0, &HelloComponent::hello);
	}

	void
	hello(const char* str)
	{
		std::cout << "[HelloComponent] " << str << std::endl;
	}

	void
	update(Entity& e, const char* str)
	{
		std::cout << "UPDATE: " << str << std::endl;
		e.send(0, "Hello, World!");
	}
};

class TotoComponent : public EntityComponent
{
	LUMS_COMPONENT

public:
	TotoComponent()
	{
		bind(0, &TotoComponent::hello);
		bind(1, &TotoComponent::cat);
	}

	void
	hello(const char* str)
	{
		std::cout << "[TotoComponent] (I am here too) " << str << std::endl;
	}

	void
	cat()
	{
		std::cout << "[TotoComponent] Meow !" << std::endl;
	}
};

int
main()
{
	Entity go;
	go.attach<HelloComponent>();
	go.attach<TotoComponent>();
	go.send(0, "Hi there");
	go.send(0, "This is a test");
	go.send(1);
	std::cout << go.composed<HelloComponent>() << std::endl;
	std::cout << go.composed<TotoComponent>() << std::endl;
	go.update("This is an Update");
	go.detach<TotoComponent>();
	go.send(0, "Hi there");
	go.send(0, "This is a test");
	go.send(1);
	std::cout << go.composed<HelloComponent>() << std::endl;
	std::cout << go.composed<TotoComponent>() << std::endl;
	go.update("This is an update");
}
