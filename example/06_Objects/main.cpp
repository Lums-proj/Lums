#include <iostream>
#include <Lums>

class HelloComponent : public lm::Component
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
};

class TotoComponent : public lm::Component
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
	lm::GameObject go;
	go.addComponent(new HelloComponent);
	go.addComponent(new TotoComponent);
	go.send(0, "Hi there");
	go.send(0, "This is a test");
	go.send(1);
}
