#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	//std::cout << "Default constructor is called" << std::endl;
	this->_importDatabase("data.csv");
	return ; 
}


BitcoinExchange::BitcoinExchange(BitcoinExchange const& other)
{
	this->_table = other._table;
}


BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& other)
{
	if (this != &other)
	{
		this->_table = other._table;
	}
	return *this;
}


BitcoinExchange::~BitcoinExchange(void)
{
	//std::cout << "Default deconstructor is called" << std::endl;
	return ; 
}


void	BitcoinExchange::_importDatabase(std::string const& fname)
{
	std::string line;
	
	std::ifstream ifs(fname.c_str());
	if (!ifs.is_open())
	{
		throw std::invalid_argument("Error: could not open the database file");
	}
	if (!std::getline(ifs, line))
	{
		throw	std::invalid_argument("Error while reading database header.");
	}
	if (line.compare("date,exchange_rate") != 0)
	{
		throw	std::invalid_argument("Error: wrong database header");
	}	
	while (std::getline(ifs, line))
		this->_processDataLine(line);
	if (ifs.bad())
	{
		throw	std::invalid_argument("Error while reading database");
	}
	if (this->_table.size() == 0)
	{
		throw	std::invalid_argument("Error: database is empty");
	}
	return ;
}


void	BitcoinExchange::_processDataLine(std::string const& line)
{
	std::string	date;
	std::string	valueStr;
	float		value;
	size_t		indComma;
	char*		endptr = NULL;

	indComma = line.find_first_of(",");
	if (indComma == std::string::npos || indComma == line.size() - 1)
		throw	std::invalid_argument("Error: wrong entry in database");
	date = line.substr(0, indComma);
	try
	{
		this->_checkDateValid(date);
	}
	catch (std::exception const& e)
	{
		std::string err("Error: wrong entry in database\n");
		err.append(e.what());
		throw	std::invalid_argument(err); 
	}
	valueStr = line.substr(indComma + 1);
	value = strtof(valueStr.c_str(), &endptr);
	if (*endptr)
		throw	std::invalid_argument("Error: wrong entry in database");
	if (value < 0 || value == HUGE_VALF)
		throw	std::invalid_argument("Error: wrong entry in database");
	this->_table.insert(std::pair<std::string, float>(date, value));
	return ;
}


float	BitcoinExchange::getPrice(std::string const& date) const
{
	this->_checkDateValid(date);
	
	std::map<std::string,float>::const_iterator itup;
	itup = this->_table.upper_bound(date);
	if (itup == this->_table.begin())
		throw	std::invalid_argument("Error: input date is earlier than database");
	itup--;
	return (itup->second);
}


void BitcoinExchange::_checkDateValid(std::string const& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		throw std::invalid_argument(std::string("Error: bad input => ").append(date));
	}


	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	if (year < 2009)
	{
		throw std::invalid_argument(std::string("Error: btc value starts in 2009 => ").append(date));
	}
	if (month < 1 || month > 12 || day < 1 || day > 31) {
		throw std::invalid_argument(std::string("Error: invalid date => ").append(date));
	}

	time_t now = time(0);
	struct tm tm;
	tm.tm_sec = 0;
	tm.tm_min = 0;
	tm.tm_hour = 0;
	tm.tm_mday = day;
	tm.tm_mon = month - 1;
	tm.tm_year = year - 1900;
	tm.tm_isdst = -1;

	time_t etime = mktime(&tm);
	if (etime > now)
	{
		throw std::invalid_argument(std::string("Error: this program doesn't make future prediction => ").append(date));
	}
}