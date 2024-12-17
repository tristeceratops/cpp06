#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data data;
	data.width = 42;
	data.str = "Hello, world!";
	data.money = 3.14f;

	uintptr_t raw = Serializer::serialize(&data);
	Data *ptr = Serializer::deserialize(raw);

	std::cout << "width: " << ptr->width << std::endl;
	std::cout << "str: " << ptr->str << std::endl;
	std::cout << "money: " << ptr->money << std::endl;

	delete ptr;

	return 0;
}