#ifndef RPN_H
# define RPN_H

# include <iostream>
# include <cctype>
# include <cstdlib>
# include <string>
# include <stack>
 //arthoooooothooooccsss cononnicsslllllll
class RPN
{
	public:
		RPN(std::string const&);
		RPN(void);
		RPN(RPN const&);
		RPN&	operator=(RPN const&);
		~RPN(void);

	private:
		
		void	check_input(std::string const&);
		void	the_calculator(char c);

		std::stack<int>	_stack;
};

#endif