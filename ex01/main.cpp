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

	Data data2;
	data2.width = 2147483647;
	data2.str = "";
	data2.money = -80.8888888888888f;

	uintptr_t raw2 = Serializer::serialize(&data2);
	Data *ptr2 = Serializer::deserialize(raw2);

	std::cout << "width: " << ptr2->width << std::endl;
	std::cout << "str: " << ptr2->str << std::endl;
	std::cout << "money: " << ptr2->money << std::endl;

	return 0;
}