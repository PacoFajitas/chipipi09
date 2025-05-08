/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:48:08 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/07 18:44:26 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <iostream>
# include <vector>
# include <cmath>
# include <deque>

class PmergeMe
{
private:
	std::vector<int> mainV;
	std::vector<int> pendV;
	std::deque<int> mainD;
	std::deque<int> pend;
	int	depth;
public:
	class InvalidInputException : public std::exception
		{
			public:
				const char* what() const throw();
		};
	PmergeMe();
	PmergeMe(int argc, char**argv);
	PmergeMe(PmergeMe &old);
	PmergeMe& operator=(PmergeMe& old);
	~PmergeMe();
	void 	makePairsV(int depth, size_t times);
	void 	binarySortV(size_t times);
	int 	nextJacobstahl(int current);
	void	initMainAndPendIndV(std::vector<int> &mainInd, std::vector<int> tmpMain, int times, std::vector<int> &pendInd);
	int		searchCurrIndexV(std::vector<int>::iterator &pendIndIt, int &jacobNum, int &oldJacob);
	void 	initBoundsV(std::vector<int> tmpMain, std::vector<int> &bounds, int times);
	void 	initTmpMainV(std::vector<int> &tmpMain,std::vector<int> mainInd,std::vector<int> bounds);
	int		findValinBoundsV(std::vector<int> bounds, int index);
	void	binaryInsertV(std::vector<int> &mainInd, std::vector<int> &tmpMain, std::vector<int> bounds,int bound, int indToPlace);
	void	changeMainV(std::vector<int> tmpMain, int times);
	void 	makePairsD(int depth, size_t times);
	void 	binarySortD(size_t times);
	void	initMainAndPendIndD(std::deque<int> &mainInd, std::deque<int> tmpMain, int times, std::deque<int> &pendInd);
	int		searchCurrIndexD(std::deque<int>::iterator &pendIndIt, int &jacobNum, int &oldJacob);
	void 	initBoundsD(std::deque<int> tmpMain, std::deque<int> &bounds, int times);
	void 	initTmpMainD(std::deque<int> &tmpMain,std::deque<int> mainInd,std::deque<int> bounds);
	int		findValinBoundsD(std::deque<int> bounds, int index);
	void	binaryInsertD(std::deque<int> &mainInd, std::deque<int> &tmpMain, std::deque<int> bounds,int bound, int indToPlace);
	void	changeMainD(std::deque<int> tmpMain, int times);
	void	printVector();
	void	printDeque();
	void	sortV();
	void	sortD();
};



#endif