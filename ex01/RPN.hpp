#ifndef RPN_H
# define RPN_H

# include <iostream>
# include <cctype>
# include <cstdlib>
# include <string>
# include <stack>

class RPN
{
	public:
		RPN(std::string const& input);
		// RPN(void);
		RPN(RPN const& copy);
		RPN&	operator=(RPN const&);
		~RPN(void);

	private:
		
		void	check_input(std::string const&);
		void	the_calculator(char c);

		std::stack<int>	_stack;
};

#endif