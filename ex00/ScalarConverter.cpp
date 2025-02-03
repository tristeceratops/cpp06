#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

void ScalarConverter::convert(const std::string &input) {
	char charValue;
	int intValue;
	float floatValue;
	double doubleValue;

	bool charPossible = true;
	bool intPossible = true;
	bool floatPossible = true;
	bool doublePossible = true;

	// Check if input is a single character
	if (input.length() == 1 && !std::isdigit(input[0])) {
		charValue = input[0];
		intValue = static_cast<int>(charValue);
		floatValue = static_cast<float>(charValue);
		doubleValue = static_cast<double>(charValue);
	} else if (input.find_first_not_of(' ') != 0){
		charPossible = false;
		intPossible = false;
		floatPossible = false;
		doublePossible = false;
	}
	else if (input == "+inf" || input == "-inf" || input == "nan" ||
			input == "+inff" || input == "-inff" || input == "nanf") {
			intPossible = false;
			charPossible = false;
			if (input[input.size() - 2] == 'f') {
				floatValue = (input == "+inff") ? std::numeric_limits<float>::infinity() :
							 (input == "-inff") ? -std::numeric_limits<float>::infinity() :
							 std::numeric_limits<float>::quiet_NaN();
				doubleValue = static_cast<double>(floatValue);
			} else {
				doubleValue = (input == "+inf") ? std::numeric_limits<double>::infinity() :
							  (input == "-inf") ? -std::numeric_limits<double>::infinity() :
							  std::numeric_limits<double>::quiet_NaN();
				floatValue = static_cast<float>(doubleValue);
			}
	}
	else {
		// Try converting to int
		std::istringstream issInt(input);
		if (!(issInt >> intValue) || !issInt.eof())
			intPossible = false;

		// Try converting to float
		std::istringstream issFloat(input);
		if (!(issFloat >> floatValue) || !issFloat.eof())
			floatPossible = false;

		// Try converting to double
		std::istringstream issDouble(input);
		if (!(issDouble >> doubleValue) || !issDouble.eof())
			doublePossible = false;

		// Check if input is printable for char
		if (intPossible && intValue >= 0 && intValue <= 127 && std::isprint(intValue))
			charValue = static_cast<char>(intValue);
		else
			charPossible = false;
	}

	// Output results
	std::cout << "char: ";
	if (charPossible)
		std::cout << "'" << charValue << "'" << std::endl;
	else if (intPossible && intValue >= 0 && intValue <= 127 && !std::isprint(intValue))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;

	std::cout << "int: ";
	if (intPossible)
		std::cout << intValue << std::endl;
	else
		std::cout << "impossible" << std::endl;

	std::cout << "float: ";
	if (floatPossible)
		std::cout << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
	else
		std::cout << "impossible" << std::endl;

	std::cout << "double: ";
	if (doublePossible)
		std::cout << std::fixed << std::setprecision(1) << doubleValue << std::endl;
	else
		std::cout << "impossible" << std::endl;
}
