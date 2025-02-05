#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(){}

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
	std::pair<bool, char> valueChar;
	std::pair<bool, int> valueInt;
	std::pair<bool, float> valueFloat;
	std::pair<bool, double> valueDouble;
	valueChar.first = true;
	valueInt.first = true;
	valueFloat.first = true;
	valueDouble.first = true;
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
		valueChar.second = input.at(0);
		valueInt.second = static_cast<int>(valueChar.second);
		valueFloat.second = static_cast<float>(valueChar.second);
		valueDouble.second = static_cast<double>(valueChar.second);
	}
	if (type == INT)
	{
		std::stringstream ss(input);
		if (!(ss >> valueInt.second))
		{
			type = DOUBLE;
			valueInt.first = false;
		}
		else
		{
			if (valueInt.second < 0 || valueInt.second > std::numeric_limits<char>::max())
				valueChar.first = false;
			else
				valueChar.second = static_cast<char>(valueInt.second);
			valueFloat.second = static_cast<float>(valueInt.second);
			valueDouble.second = static_cast<double>(valueInt.second);
		}
	}
	if (type == FLOAT)
	{
		bool isInf = false;
		if (input == "+inff" || input == "-inff" || input == "nanf")
		{
			isInf = true;
			if (input == "+inff")
				valueFloat.second = std::numeric_limits<float>::infinity();
			else if (input == "-inff")
				valueFloat.second = -std::numeric_limits<float>::infinity();
			else
				valueFloat.second = std::numeric_limits<float>::quiet_NaN();
		}
		else
		{
			std::stringstream ss(input);
			if (!(ss >> valueFloat.second))
				valueFloat.first = false;
		}
		if (isInf || (valueFloat.second < 0 && valueFloat.second > std::numeric_limits<char>::max()))
			valueChar.first = false;
		else
			valueChar.second = static_cast<char>(valueFloat.second);
		if (isInf || valueFloat.second < std::numeric_limits<int>::min() || valueFloat.second > std::numeric_limits<int>::max())
			valueChar.first = false;
		else
			valueInt.second = static_cast<int>(valueFloat.second);
		valueDouble.second = static_cast<double>(valueFloat.second);
	}
	if (type == DOUBLE)
	{
		bool isInf = false;
		if (input == "+inf" || input == "-inf" || input == "nan")
		{
			isInf = true;
			if (input == "+inf")
				valueDouble.second = std::numeric_limits<double>::infinity();
			else if (input == "-inf")
				valueDouble.second = -std::numeric_limits<double>::infinity();
			else
				valueDouble.second = std::numeric_limits<double>::quiet_NaN();
		}
		else
		{
			std::stringstream ss(input);
			if (!(ss >> valueDouble.second))
				valueDouble.first = false;
		}
		if (isInf || (valueDouble.second < 0 && valueDouble.second > std::numeric_limits<char>::max()))
			valueChar.first = false;
		else
			valueChar.second = static_cast<char>(valueDouble.second);
		if (isInf || (valueDouble.second < std::numeric_limits<int>::min() || valueDouble.second > std::numeric_limits<int>::max()))
			valueInt.first = false;
		else
			valueInt.second = static_cast<int>(valueDouble.second);
		if ((valueDouble.second < std::numeric_limits<float>::min() || valueDouble.second > std::numeric_limits<float>::max()) && !isInf)
			valueFloat.first = false;
		else
			valueFloat.second = static_cast<float>(valueDouble.second);
	}

	std::cout << "char: ";
	if (valueChar.first && isprint(valueChar.second))
		std::cout << "'" << valueChar.second << "'" << std::endl;
	else if (valueChar.first)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "impossible" << std::endl;
	if (valueInt.first)
		std::cout << "int: " << valueInt.second << std::endl;
	else
		std::cout << "int: impossible" << std::endl;
	if (valueFloat.first)
		std::cout << "float: " << std::fixed << std::setprecision(1) << valueFloat.second << "f" << std::endl;
	else
		std::cout << "float: impossible" << std::endl;
	if (valueFloat.first)
		std::cout << "double: " << std::fixed << std::setprecision(1) << valueDouble.second << std::endl;
	else
		std::cout << "double: impossible" << std::endl;
}
