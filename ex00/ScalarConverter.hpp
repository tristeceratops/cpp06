#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>


class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		~ScalarConverter();
	public:
		ScalarConverter &operator=(const ScalarConverter &other);

		static void convert(const std::string &input);
};