/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:49:38 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/25 22:36:23 by tfiguero         ###   ########.fr       */
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
		mainV.push_back(std::atoi(argv[i]));
	}
	this->depth = ft_getdepth(mainV.size(), 0);
	makePairs(this->depth, 1);
	
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
static void printVector(std::vector<int> vector)
{
	std::vector<int>::iterator it = vector.begin();
	std::cout << "The values of this vector are: ";
	while(it!= vector.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
static std::vector<int> excludeUnpaired(std::vector<int> base, int times)
{
	std::vector<int> ret;
	int	pairs = pow(2, times);
	int excluded = base.size() %  pairs;
	ret = base;
	while (excluded > 0)
	{
		ret.pop_back();
		excluded--;
	}
	return ret;
}
void PmergeMe::makePairs(int depth, size_t times)
{
	if (depth==0)
		return ;	
	std::vector<int> tmp;
	tmp = excludeUnpaired(this->mainV, times);
	size_t pairs = pow(2, times);
	size_t lastPair = pairs/2;
	size_t i = lastPair-1;
	std::cout << "Pairs is: " << pairs << std::endl;
	while(i < (tmp.size() - lastPair))
	{
			if(tmp.at(i) <= tmp.at(i + lastPair))
			{
				i+=pairs;
				continue;
			}
			for (int j = lastPair-1; j >= 0; j--)
			{
				int	&firstNumber = tmp.at(i - j);
				int	&secondNumber = tmp.at(i - j +lastPair);
				std::swap(firstNumber, secondNumber);
			}
		
		i += pairs;
	}
	int excluded = this->mainV.size() %  pairs;
	while (excluded > 0)
	{
		int it;
		std::vector<int>::iterator it2;
		
		it=*(mainV.end()-excluded);
		it2 = tmp.end();
		tmp.insert(it2, it);
		excluded--;
	}
	this->mainV = tmp;
	std::cout << "Vector after recuersion level: " << times << " is: " << std::endl;
	printVector(this->mainV);
	makePairs(depth-1, times+1);
	binarySort(times);
}

void PmergeMe::binarySort(size_t times)
{
	times = 1;
}

int PmergeMe::nextJacobstahl(int current)
{
	int ret;
	int old;
	ret = 3;
	old = 1;
	while(ret <= current)
	{
		ret += (old*2);
		old = ret-(old*2);
	}
	return ret;
}

const char * PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid arguments";
}
