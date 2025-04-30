#include "BitcoinExchange.hpp"


void	get_date_and_amount(std::string const& line, std::string& date, float& float_amount, int& int_amount, bool& isFloat)
{
	std::string	amount;
	char *endptr = NULL;

	if (line.length() < 14 || line[10] != ' ' || line[11] != '|' || line[12] != ' ')
		throw std::invalid_argument(std::string("Error: bad input(space/pipe)=> ").append(line));
	date = line.substr(0, 10);	
	amount = line.substr(13);
	if (amount.find_first_of('.') != std::string::npos)
	{
		float_amount = strtof(amount.c_str(), &endptr);
		if (*endptr)
			throw std::invalid_argument(std::string("Error: bad input => ").append(line));
		else if (float_amount < 0)
			throw std::invalid_argument("Error: not a positive number.");
		else if (float_amount > 1000.0f)
			throw std::invalid_argument("Error: too large a (float) number.");
		isFloat = true;
	}
	else
	{
		long tmp = strtol(amount.c_str(), &endptr, 10);
		if (*endptr)
			throw std::invalid_argument(std::string("Error: bad input => ").append(line));
		else if (tmp < 0)
			throw std::invalid_argument("Error: not a positive number.");
		else if (tmp > 1000)
			throw std::invalid_argument("Error: too large a number.");
		int_amount = (int)tmp;
		isFloat = false;
	}
}


void	process_request_line(std::string const& line, BitcoinExchange const& btx)
{
	std::string	date;
	float	float_amount;
	int		int_amount;
	bool	isFloat;
	float	price;

	try
	{
		get_date_and_amount(line, date, float_amount, int_amount, isFloat);
		price = btx.getPrice(date);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
	if (isFloat)
        std::cout << date << " => " << std::fixed << std::setprecision(2) << float_amount << " = " << std::fixed << std::setprecision(2) << price * float_amount << std::endl;
    else
        std::cout << date << " => " << std::fixed << std::setprecision(2) << int_amount << " = " << std::fixed << std::setprecision(2) << price * int_amount << std::endl;
	// if (isFloat)
	// 	std::cout << date << " => " << float_amount << " = " << price * float_amount << std::endl;
	// else
	// 	std::cout << date << " => " << int_amount << " = " << price * int_amount << std::endl;
}


void	process_input_request(std::string const& file_name, BitcoinExchange const& btc)
{
	std::string line;
	
	std::ifstream input_file_stream(file_name.c_str());
	if (!input_file_stream.is_open()) 
		throw std::invalid_argument("Error: could not open the input file");
	if (!std::getline(input_file_stream, line))
		throw	std::invalid_argument("Error while reading input header.");
	if (line.compare("date | value") != 0)
		throw	std::invalid_argument("Error: wrong input header");
	while (std::getline(input_file_stream, line))
		process_request_line(line, btc);
	if (input_file_stream.bad())
		throw	std::invalid_argument("Error while reading input file");
}


int	main(int ac, char**av)
{
	if (ac != 2 || av[1][0] == '\0')
	{
		std::cout << "Error: need one filename as input" << std::endl;
		exit(EXIT_FAILURE);
	}	
	try
	{
		BitcoinExchange	btc;
		process_input_request(av[1], btc);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}


//std::fixed() << std::setpercision(2)    scientefic

//basic string when there is a new line in the csv file