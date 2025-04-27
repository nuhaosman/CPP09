#include "RPN.hpp"

int main(int ac, char** av)
{
	if (ac != 2 || av[1][0] == '\0')
	{
		std::cout << "Error: ./RPN \"operands/operators\"" << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		RPN rpn(av[1]);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}
}