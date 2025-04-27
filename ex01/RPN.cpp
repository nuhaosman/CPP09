#include "RPN.hpp"


RPN::RPN(std::string const& input)
{
    //std::cout << "RPN param ctor called" << std::endl;
    this->check_input(input);
}

RPN::~RPN(void)
{
    //std::cout << "RPN dtor called" << std::endl;
}

void RPN::check_input(std::string const& input)
{

    for (size_t i = 0; i < input.size(); ++i)
    {
        char number = input[i];

        if (number == '-' && (i + 1 < input.size() && isdigit(input[i + 1])))
        {
            throw std::invalid_argument("Error: negative numbers are not allowed");
        }
        else if (isdigit(number))
        {
            _stack.push(static_cast<int>(number - '0'));
        }
        else if (number == '+' || number == '-' || number == '*' || number == '/')
        {
            the_calculator(number);
        }
        else if (number != ' ')
        {
            throw std::invalid_argument("Error: invalid argument");
        }
    }

    if (_stack.size() > 1)
        throw std::invalid_argument("Error: stack should have only one number inside!");

    std::cout << _stack.top() << std::endl;
}

void RPN::the_calculator(char c)
{
    int first_num;
	int second_num;
	int result;

    if (_stack.size() < 2)
        throw std::invalid_argument("Error: operation can not be completed due to insufficient elements");
    
    second_num = _stack.top();
    _stack.pop();
    first_num = _stack.top();
    _stack.pop();

    if (c == '+')
        result = first_num + second_num;
    else if (c == '-')
        result = first_num - second_num;
    else if (c == '*')
        result = first_num * second_num;
    else if (c == '/')
    {
        if (second_num == 0)
            throw std::invalid_argument("Error: Can not divide by zero!");
        result = first_num / second_num;
    }

    _stack.push(result);  
}