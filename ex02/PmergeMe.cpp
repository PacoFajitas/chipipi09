/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:49:38 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/21 01:54:00 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

static int ft_getdepth(int vals, int ret)
{
	if(vals >= 2)
		ret = ft_getdepth(vals/2, ret+1);
	return ret;
}
PmergeMe::PmergeMe(int argc, char **argv)
{
	std::vector<int> base;
	if (argc <= 1)
		throw PmergeMe::InvalidInputException();
	for (int i = 1; i < argc; i++)
	{
		int j = 0;
		while(argv[i][j])
		{
			if(argv[i][j] < '0' || argv[i][j] > '9')
			{
				throw PmergeMe::InvalidInputException();
			}
			j++;
		}
		base.push_back(std::atoi(argv[i]));
		this->data.push_back(base);
		base.clear();
	}
	printVectorBase();
	this->depth = ft_getdepth(data.size(), 0);
	std::cout << this->depth << std::endl;
	
}

PmergeMe::PmergeMe(PmergeMe & old)
{
	*this = old;
}

PmergeMe & PmergeMe::operator=(PmergeMe & old)
{
	(void)  old;
	return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::printVectorBase()
{
	for (size_t i = 0; i < this->data.size(); i++)
	{
		std::cout << "En el vector de la posicion :" << i << " Estan los numeros :" ;
		for (size_t j = 0; j < this->data[i].size(); j++)
		{
			std::cout << this->data[i][j] << "  ";
		}
		std::cout << std::endl;
		
	}
	
}

const char * PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid arguments";
}
