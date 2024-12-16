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

void ScalarConverter::convert(const std::string &input)
{
    int type = 0; // 0 = int, 1 = float, 2 = double
    if (input.length() == 1 && !isdigit(input.at(0)))
    {
        if (input.at(0) < 32 || input.at(0) > 126)
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << input.at(0) << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(input.at(0)) << std::endl;
        std::cout << "float: " << static_cast<float>(input.at(0)) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(input.at(0)) << ".0" << std::endl;
        return;
    }
    else if (input == "-inff" || input == "+inff" || input == "nanf")
    {
        type = 1;
    }
    else if (input == "-inf" || input == "+inf" || input == "nan")
    {
        type = 2;
    }
    else if (input.length() > 0 && input.at(input.length() - 1) == 'f')
    {
        type = 1;
    }
    else
    {
        for (size_t i = 0; i < input.length(); i++)
        {
            if (input.at(i) == '.')
            {
                type = 2;
                break;
            }
        }
    }

    if (type == 0)
    {
        try
        {
            std::stringstream ss(input);
            int i;
            ss >> i;
            if (ss.fail() || !ss.eof())
                throw std::invalid_argument("Invalid argument");
            std::cout << "char: ";
            if (i < 0 || i > 255)
				std::cout << "impossible" << std::endl;
			else if (i < 32 || i > 126)
                std::cout << "Non displayable" << std::endl;
            else
                std::cout << "'" << static_cast<char>(i) << "'" << std::endl;
            std::cout << "int: " << i << std::endl;
            std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
            std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
        }
    }
    else if (type == 1)
    {
        try
        {
            float f;
            float fractal = -1, integral = -1;
            if (input == "-inff")
                f = -std::numeric_limits<float>::infinity();
            else if (input == "+inff")
                f = std::numeric_limits<float>::infinity();
            else if (input == "nanf")
                f = std::numeric_limits<float>::quiet_NaN();
            else
            {
                std::string s = input.substr(0, input.length() - 1);
                std::stringstream ss(s);
                ss >> f;
                if (ss.fail() || !ss.eof())
                    throw std::invalid_argument("Invalid argument");
            	fractal = std::modf(f, &integral);
            }
            std::cout << "char: ";
			if (f < 0 || f > 255 || std::isnan(f) || std::isinf(f))
				std::cout << "impossible" << std::endl;
            else if (f < 32 || f > 126 )
                std::cout << "Non displayable" << std::endl;
            else
                std::cout << "'" << static_cast<char>(f) << "'" << std::endl;
            std::cout << "int: ";
            if (f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min() || std::isnan(f) || std::isinf(f))
                std::cout << "impossible" << std::endl;
            else
                std::cout << static_cast<int>(f) << std::endl;
            std::cout << "float: " << f << "f" << std::endl;
            std::cout << "double: " << static_cast<double>(f) << ((fractal == 0) ? ".0" : "") << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
        }
    }
    else if (type == 2)
    {
        try
        {
            double d;
            double fractal = -1, integral = -1;
            if (input == "-inf")
                d = -std::numeric_limits<double>::infinity();
            else if (input == "+inf")
                d = std::numeric_limits<double>::infinity();
            else if (input == "nan")
                d = std::numeric_limits<double>::quiet_NaN();
            else
            {
                std::stringstream ss(input);
                ss >> d;
                if (ss.fail() || !ss.eof())
                    throw std::invalid_argument("Invalid argument");
            	fractal = std::modf(d, &integral);
            }
            std::cout << "char: ";
            if (d < 0 || d > 255 || std::isnan(d) || std::isinf(d))
				std::cout << "impossible" << std::endl;
			else if (d < 32 || d > 126)
                std::cout << "Non displayable" << std::endl;
            else
                std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
            std::cout << "int: ";
            if (d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min() || std::isnan(d) || std::isinf(d))
                std::cout << "impossible" << std::endl;
            else
                std::cout << static_cast<int>(d) << std::endl;
            std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
            std::cout << "double: " << d << ((fractal == 0) ? ".0" : "") << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
        }
    }
    else
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
}