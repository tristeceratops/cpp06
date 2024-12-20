#include "Function.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int main(void)
{
	Base *baseA;
	Base *baseB;
	Base *baseC;
	Base *rand;

	srand(time(0));

	baseA = new A();
	baseB = new B();
	baseC = new C();

	identify(baseA);
	identify(baseB);
	identify(baseC);

	identify(*baseA);
	identify(*baseB);
	identify(*baseC);

	std::cout << "/////RAND/////" << std::endl;

	for (int i = 0; i < 50; i++)
	{
		rand = generate();
		identify(rand);
		delete rand;
	}
	
	delete baseA;
	delete baseB;
	delete baseC;

	return 0;
}


