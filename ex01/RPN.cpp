/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:43:00 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/02 13:13:03 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}
RPN::RPN(const RPN& old)
{
	*this = old;
}
RPN& RPN::operator=(const RPN& old)
{
	if(this != &old)
		this->_nums = old._nums;
	return *this;
}

RPN::~RPN()
{
}
void RPN::evaluate(std::string arg)
{
	for (size_t i = 0; i < arg.length(); i++)
	{
		
		if (arg.at(i) == '+' ||arg.at(i) == '-'||arg.at(i) == '/'||arg.at(i) == '*' )
			this->calculate(arg.at(i));
		else if(arg.at(i) >= '0' && arg.at(i) <= '9')
		{
			this->_nums.push((arg.at(i) - '0'));
		}
		else if(arg.at(i) == ' ')
		{}
		else
			throw RPN::excpetionError();
	}
	if (_nums.size() == 1)
		std::cout <<_nums.top() << std::endl;
}
void RPN::calculate(char oper)
{
	int a, b;
	if (_nums.size() < 2)
		throw RPN::excpetionError();
	b = _nums.top();
	_nums.pop();
	a = _nums.top();
	_nums.pop();
	switch (oper)
	{
	case '*':
		_nums.push(a * b);
		break;
	case '/':
		_nums.push(a / b);
		break;
	case '-':
		_nums.push(a - b);
		break;
	default:
		_nums.push(a + b);
		break;
	}	
}

const char* RPN::excpetionError::what() const throw()
{
	return("Error");
}
