#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <string>


bool input_parsing(int argc, char *argv[], std::vector<int> &input)
{
	char *endptr;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		// Check for non-digit characters
		for (std::string::iterator it = arg.begin(); it != arg.end(); ++it)
		{
			if (!std::isdigit(*it))
			{
				std::cerr << "Error: Invalid input.\n";
				return false;
			}
		}
		// When you call std::strtol, it takes a string (in this case, argv[i])
		// and attempts to convert it to a long integer. The function also takes
		// a pointer to a char (endptr) that will point to the first character in
		// the string that was not converted.
		// If the entire string is a valid number, endptr will point to the null
		// terminator ('\0') at the end of the string. If there are non-numeric
		// characters in the string, endptr will point to the first of those characters.
		long num = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || num <= 0 || num > 2147483647)
		{
			std::cerr << "Error: '" << arg << "' is not a valid positive integer or is out of range.\n";
			return false;
		}
		input.push_back(static_cast<int>(num));
	}
	return true;
}

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		std::cerr << "Error: No input provided, enter a sequence of positive integers.\n";
		return 1;
	}
	if (argc == 2)
	{
		std::cout << "Enter more than one number.\n";
		return 1;
	}

	std::vector<int> input;
	if (!input_parsing(argc, argv, input))
		return 1;

	PmergeMe sorter(input);
	std::cout << "Before:\n";
	sorter.printSequence();
	std::cout << "\n";

	sorter.sortWithVector();
	sorter.sortWithList();

	std::cout << "After: ";
	sorter.printSequence();
	std::cout << "\n";
	sorter.printTimings();

	return 0;
}