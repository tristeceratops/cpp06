#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

void identify(Base *p)
{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "NULL" << std::endl;
}

void identify(Base &p)
{	
	try
	{
		if (dynamic_cast<A*>(&p))
			std::cout << "A" << std::endl;
	}
	catch(const std::bad_cast& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		if (dynamic_cast<B*>(&p))
			std::cout << "B" << std::endl;
	}
	catch(const std::bad_cast& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		if (dynamic_cast<C*>(&p))
			std::cout << "C" << std::endl;
	}
	catch(const std::bad_cast& e)
	{
		std::cerr << "Bad cast: " << e.what() << '\n';
	}
	
}
