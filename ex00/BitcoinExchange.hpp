#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <ctime>
# include <cmath>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const&);
		BitcoinExchange&	operator=(BitcoinExchange const&);
		~BitcoinExchange(void);
		
		float	getPrice(std::string const&) const;

	private:
		
		void	_importDatabase(std::string const&);
		void	_processDataLine(std::string const&);
		void	_checkDateValid(std::string const& date) const;

		std::map<std::string, float>	_table;

};

#endif