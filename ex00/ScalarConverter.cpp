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

bool isInt(const std::string &input)
{
	if (input.at(0) != '+' && input.at(0) != '-' && !isdigit(input.at(0)))
		return false;
	for (size_t i = 1; i < input.size(); i++)
	{
		if (!isdigit(input.at(i)))
			return false;
	}
	return true;
	
}

bool isFloat(const std::string &input)
{
	bool dot = false;
	bool f = false;

	if (input == "+inff" || input == "-inff" || input == "nanf")
		return true;
	if (input.at(0) != '+' && input.at(0) != '-' && input.at(0) != '.' && !isdigit(input.at(0)))
		return false;
	dot = (input.at(0) == '.');
	for (size_t i = 1; i < input.size(); i++)
	{
		if (!isdigit(input.at(i)) && (input.at(i) != '.' || dot) && (input.at(i) != 'f' || f))
			return false;
		if (input.at(i) == '.')
			dot = true;
		if (input.at(i) == 'f')
			f = true;
	}
	return (f);
}

bool isDouble(const std::string &input)
{
	bool dot = false;

	if (input == "+inf" || input == "-inf" || input == "nan")
		return true;
	if (input.at(0) != '+' && input.at(0) != '-' && input.at(0) != '.' && !isdigit(input.at(0)))
		return false;
	dot = (input.at(0) == '.');
	for (size_t i = 1; i < input.size(); i++)
	{
		if (!isdigit(input.at(i)) && (input.at(i) != '.' || dot))
			return false;
		if (input.at(i) == '.')
			dot = true;
	}
	return true;
}

void ScalarConverter::convert(const std::string &input)
{
	eType type = NONE;
	int charPossible = true;
	bool intPossible = true;
	bool floatPossible = true;
	bool doublePossible = true;
	char valueChar;
	int valueInt;
	float valueFloat;
	double valueDouble;
	size_t size = input.size();

	if(size == 1)
		type = CHAR;
	else if (size > 1)
	{
		if(isInt(input))
			type = INT;
		else if(isFloat(input))
			type = FLOAT;
		else if(isDouble(input))
			type = DOUBLE;
	}
	
	if (type == NONE)
	{
		std::cerr << "char: impossible" << std::endl;
		std::cerr << "int: impossible" << std::endl;
		std::cerr << "float: impossible" << std::endl;
		std::cerr << "double: impossible" << std::endl;
		return;
	}
	if (type == CHAR)
	{
		valueChar = input.at(0);
		valueInt = static_cast<int>(valueChar);
		valueFloat = static_cast<float>(valueChar);
		valueDouble = static_cast<double>(valueChar);
	}
	if (type == INT)
	{
		std::stringstream ss(input);
		if (!(ss >> valueInt))
		{
			type = DOUBLE;
			intPossible = false;
		}
		else
		{
			if (valueInt < 0 || valueInt > std::numeric_limits<char>::max())
				charPossible = false;
			else
				valueChar = static_cast<char>(valueInt);
			valueFloat = static_cast<float>(valueInt);
			valueDouble = static_cast<double>(valueInt);
		}
	}
	if (type == FLOAT)
	{
		bool isInf = false;
		if (input == "+inff" || input == "-inff" || input == "nanf")
		{
			isInf = true;
			if (input == "+inff")
				valueFloat = std::numeric_limits<float>::infinity();
			else if (input == "-inff")
				valueFloat = -std::numeric_limits<float>::infinity();
			else
				valueFloat = std::numeric_limits<float>::quiet_NaN();
		}
		else
		{
			std::stringstream ss(input);
			if (!(ss >> valueFloat))
			{
				floatPossible = false;
			}
		}
		if (isInf || (valueFloat < 0 && valueFloat > std::numeric_limits<char>::max()))
			charPossible = false;
		else
			valueChar = static_cast<char>(valueFloat);
		if (isInf || valueFloat < std::numeric_limits<int>::min() || valueFloat > std::numeric_limits<int>::max())
			intPossible = false;
		else
			valueInt = static_cast<int>(valueFloat);
		valueDouble = static_cast<double>(valueFloat);
	}
	if (type == DOUBLE)
	{
		bool isInf = false;
		if (input == "+inf" || input == "-inf" || input == "nan")
		{
			isInf = true;
			if (input == "+inf")
				valueDouble = std::numeric_limits<double>::infinity();
			else if (input == "-inf")
				valueDouble = -std::numeric_limits<double>::infinity();
			else
				valueDouble = std::numeric_limits<double>::quiet_NaN();
		}
		else
		{
			std::stringstream ss(input);
			if (!(ss >> valueDouble))
			{
				doublePossible = false;
			}
		}
		if (isInf || (valueDouble < 0 && valueDouble > std::numeric_limits<char>::max()))
			charPossible = false;
		else
			valueChar = static_cast<char>(valueDouble);
		if (isInf || (valueDouble < std::numeric_limits<int>::min() || valueDouble > std::numeric_limits<int>::max()))
			intPossible = false;
		else
			valueInt = static_cast<int>(valueDouble);
		if ((valueDouble < std::numeric_limits<float>::min() || valueDouble > std::numeric_limits<float>::max()) && !isInf)
			floatPossible = false;
		else
			valueFloat = static_cast<float>(valueDouble);
	}

	std::cout << "char: ";
	if (charPossible && isprint(valueChar))
		std::cout << "'" << valueChar << "'" << std::endl;
	else if (charPossible)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;
	if (intPossible)
		std::cout << "int: " << valueInt << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
	if (floatPossible)
		std::cout << "float: " << std::fixed << std::setprecision(1) << valueFloat << "f" << std::endl;
	else
		std::cout << "float: impossible" << std::endl;
	if (doublePossible)
		std::cout << "double: " << std::fixed << std::setprecision(1) << valueDouble << std::endl;
	else
		std::cout << "double: impossible" << std::endl;
}