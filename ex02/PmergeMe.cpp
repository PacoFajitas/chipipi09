/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:49:38 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/07 17:19:45 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
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
	printVector(this->mainV);
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
	if(excludeUnpaired(this->mainV, times).size()/lastPair > 3)
		binarySort(times);
}

void PmergeMe::binarySort(size_t times)
{

	std::cout << "holiiiiiiii" << std::endl;
	std::vector<int> pend, pendInd, mainInd, tmpMain, bounds;
	int jacobNum = nextJacobstahl(3);
	int oldJacob = 1;
	tmpMain = excludeUnpaired(this->mainV, times);
	initMainAndPendInd(mainInd, tmpMain, times, pendInd);
	initBounds(tmpMain, bounds, times);
	printVector(mainInd);
	initTmpMain(tmpMain, mainInd, bounds);
	while (!pendInd.empty())
	{
		std::vector<int>::iterator pendIndIt = pendInd.begin();
		int indToPlace = searchCurrIndex(pendIndIt, jacobNum, oldJacob);
		int bound;
		if(std::find(mainInd.begin(), mainInd.end(), -indToPlace) == mainInd.end())
			bound = -indToPlace -1;
		else
			bound = -indToPlace;
		binaryInsert(mainInd, tmpMain, bounds, bound, indToPlace);
		// printVector(tmpMain);
		pendInd.erase(pendIndIt);
		// printVector(pendInd);
	}
	printVector(tmpMain);
	changeMainV(tmpMain, times);
	std::cout << "adiu" << std::endl;
	

}

void	PmergeMe::changeMainV(std::vector<int> tmpMain, int times)
{
	int lastPair = std::pow(2, times)/2;
	std::vector<int>::iterator it1 = tmpMain.begin();
	std::vector<int>::iterator it2;
	std::vector<int> fin;
	printVector(tmpMain);
	for (; it1 != tmpMain.end(); ++it1)
	{
		it2 = this->mainV.begin();
		while (*it2 != *it1)
			++it2;
		// std::cout << t << std::endl;
		for (size_t i = lastPair-1; i > 0; i--)
		{
			std::cout << "jiji" << std::endl;
			fin.push_back(*(it2-i));
		}
		std::cout << *it2 << std::endl;
		fin.push_back(*it2);
	}
	int excluded = this->mainV.size() %  lastPair;
	while (excluded > 0)
	{
		int it;
		std::vector<int>::iterator it2;
		
		it=*(mainV.end()-excluded);
		it2 = fin.end();
		fin.insert(it2, it);
		excluded--;
	}
	std::cout << "final: ";
	printVector(fin);
	std::cout << "Prev:";
	printVector(this->mainV);
	this->mainV = fin;
}

void PmergeMe::binaryInsert(std::vector<int> &mainInd, std::vector<int> &tmpMain, std::vector<int> bounds, int bound, int indToPlace)
{
    int insertVal = findValinBounds(bounds, indToPlace);
    // std::vector<int>::iterator lowIt = mainInd.begin();
    std::vector<int>::iterator highIt = std::find(mainInd.begin(), mainInd.end(), bound);

    int left = 0;
    int right = 0;
    for (std::vector<int>::iterator it = mainInd.begin(); it != highIt; ++it)
        ++right;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        std::vector<int>::iterator midIt = mainInd.begin();
        for (int i = 0; i < mid; ++i)
            ++midIt;

        int midVal = findValinBounds(bounds, *midIt);
        if (insertVal > midVal)
            left = mid + 1;
        else
            right = mid;
    }

    std::vector<int>::iterator insertIt = mainInd.begin();
    std::vector<int>::iterator tmpIt = tmpMain.begin();
    for (int i = 0; i < left; ++i)
    {
        ++insertIt;
        ++tmpIt;
    }

    mainInd.insert(insertIt, indToPlace);
    tmpMain.insert(tmpIt, insertVal);
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
		std::cout << *it << std::endl;
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
		if(*pendIndIt == jacobNum)
		{
			ret = *pendIndIt;
			break;
		}
		if (jacobNum == oldJacob)
		{
			jacobNum = nextJacobstahl(jacobNum);
			oldJacob = jacobNum;
		}
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
