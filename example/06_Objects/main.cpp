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
		bind("hello", &HelloComponent::hello);
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
		e.send("hello", "Hello, World!");
	}
};

class TotoComponent : public EntityComponent
{
	LUMS_COMPONENT

public:
	TotoComponent()
	{
		bind("hello", &TotoComponent::hello);
		bind("cat", &TotoComponent::cat);
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

class MovableComponent : public EntityComponent
{
	LUMS_COMPONENT

public:
	MovableComponent(int pos)
	: _pos(pos)
	{
		bind("position", &MovableComponent::pos);
	}

	int*
	pos()
	{
		return &_pos;
	}

private:
	int	_pos;
};

int
main()
{
	Entity go;
	go.attach<HelloComponent>();
	go.attach<TotoComponent>();
	go.attach<MovableComponent>(4242);
	go.send("hello", "Hi there");
	go.send("hello", "This is a test");
	go.send("cat");
	std::cout << go.composed<HelloComponent>() << std::endl;
	std::cout << go.composed<TotoComponent>() << std::endl;
	std::cout << *(go.recv<int>("position")) << std::endl;
	go.update("This is an Update");
	go.detach<TotoComponent>();
	go.send("hello", "Hi there");
	go.send("hello", "This is a test");
	go.send("cat");
	std::cout << go.composed<HelloComponent>() << std::endl;
	std::cout << go.composed<TotoComponent>() << std::endl;
	go.update("This is an update");
}
