#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <bits/stdc++.h>


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