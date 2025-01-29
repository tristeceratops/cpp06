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
        A &a = dynamic_cast<A&>(p);
		(void)a;
        std::cout << "A" << std::endl;
        return;
    }
    catch (const std::bad_cast& e) {}

    try
    {
        B &b = dynamic_cast<B&>(p);
		(void)b;
        std::cout << "B" << std::endl;
        return;
    }
    catch (const std::bad_cast& e) {}

    try
    {
        C &c = dynamic_cast<C&>(p);
		(void)c;
        std::cout << "C" << std::endl;
        return;
    }
    catch (const std::bad_cast& e) {}

    std::cout << "Unknown type" << std::endl;
}
