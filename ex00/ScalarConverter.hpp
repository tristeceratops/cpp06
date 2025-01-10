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
	public:
		ScalarConverter &operator=(const ScalarConverter &other);
		~ScalarConverter();

		static void convert(const std::string &input);
};