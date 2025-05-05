/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:49:38 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/05 10:21:02 by tfiguero         ###   ########.fr       */
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
	int	pairs = pow(2, times)/2;
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
	// std::cout << "Pairs is: " << pairs << std::endl;
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
	int excluded = this->mainV.size() %  lastPair;
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
	makePairs(depth-1, times+1);
	binarySort(times);
}

void PmergeMe::binarySort(size_t times)
{

		std::cout << "holiiiiiiii" << std::endl;
	std::vector<int> pend, pendInd, mainInd, tmpMain, bounds;
	int jacobNum = nextJacobstahl(3);
	int oldJacob = 1;
	tmpMain = excludeUnpaired(this->mainV, times);
	// printVector(tmpMain);
	initMainAndPendInd(mainInd, tmpMain, times, pendInd);
	// printVector(tmpMain);
	initBounds(tmpMain, bounds, times);
	printVector(bounds);
	initTmpMain(tmpMain, mainInd, bounds);
	printVector(tmpMain);
	while (!pendInd.empty())
	{
		std::vector<int>::iterator pendIndIt = pendInd.begin();
		int indToPlace = searchCurrIndex(pendIndIt, jacobNum, oldJacob);
		int bound;
		if(std::find(mainInd.begin(), mainInd.end(), -indToPlace) == mainInd.end())
			bound = -indToPlace -1;
		else
			bound = -indToPlace;
		std::vector<int>::iterator tmpMainIt = tmpMain.begin();
		for (std::vector<int>::iterator it = mainInd.begin(); *it != bound; ++it)
		{
	
			if(findValinBounds(bounds, indToPlace) < findValinBounds(bounds, *it))
			{
				mainInd.insert(it, indToPlace);
				tmpMain.insert(tmpMainIt, findValinBounds(bounds, indToPlace));
				break;
			}
			++tmpMainIt;
		}
		printVector(tmpMain);
		printVector(pendInd);
		pendInd.erase(pendIndIt);
	}
	
	
}
int	PmergeMe::findValinBounds(std::vector<int> bounds, int index)
{
	int ret;
	if(index < 0)
		ret = (-(index)*2)-1;
	else
		ret = (index)*2;
	std::vector<int>::iterator it = bounds.begin();
	while(--ret>0)
		++it;
	ret = *it;
	return ret;
}
void PmergeMe::initTmpMain(std::vector<int> &tmpMain,std::vector<int> mainInd,std::vector<int> bounds)
{
	tmpMain.clear();
	std::vector<int>::iterator it = mainInd.begin();
	while (it != mainInd.end())
	{
		int elem;
		if(*it < 0)
			elem = (-(*it)*2)-1;
		else
			elem = (*it)*2;
		std::vector<int>::iterator it2 = bounds.begin();
		while(--elem>0)
			++it2;
		tmpMain.push_back(*it2);
		++it;
	}
	
}
void PmergeMe::initBounds(std::vector<int> tmpMain, std::vector<int> &bounds, int times)
{
	int pair = pow(2, times) /2;
	size_t i = pair-1;
	while(i<tmpMain.size())
	{
		bounds.push_back(tmpMain.at(i));
		i+=pair;
	}

}

int	PmergeMe::searchCurrIndex(std::vector<int>::iterator &pendIndIt, int &jacobNum, int &oldJacob)
{
	int ret = 0;
	while (!ret)
	{
		if (jacobNum == oldJacob)
		{
			jacobNum = nextJacobstahl(jacobNum);
			oldJacob = jacobNum;
		}
		if(*pendIndIt == jacobNum)
			ret = *pendIndIt;
		jacobNum--;
	}
	return ret;
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

void PmergeMe::initMainAndPendInd(std::vector<int>& mainInd, std::vector<int> tmpMain, int times, std::vector<int>& pendInd)
{
	float pair= pow(2, times)/2;
	size_t num_elems = tmpMain.size()/pair;
	if (num_elems<=3)
	{
		mainInd.push_back(-1);
		for (size_t i = 1; i < num_elems; i++)
			mainInd.push_back(i);
	}
	else
	{
		mainInd.push_back(-1);
		mainInd.push_back(1);
		int Ind = 2;
		for (size_t i = 1; i < num_elems; i++)
		{
			if(i%2==0)
				pendInd.push_back(Ind *-1);
			else if(i != 1)
			{	
				mainInd.push_back(Ind);
				Ind++;
			}		
		}
	}
}





const char * PmergeMe::InvalidInputException::what() const throw()
{
	return "Invalid arguments";
}
