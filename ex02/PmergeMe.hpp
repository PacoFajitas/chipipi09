/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:48:08 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/05 12:12:27 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <iostream>
# include <vector>
# include <cmath> 

class PmergeMe
{
private:
	std::vector<int> mainV;
	std::vector<int> pend;
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
	void 	makePairs(int depth, size_t times);
	void 	binarySort(size_t times);
	int 	nextJacobstahl(int current);
	void	initMainAndPendInd(std::vector<int> &mainInd, std::vector<int> tmpMain, int times, std::vector<int> &pendInd);
	int		searchCurrIndex(std::vector<int>::iterator &pendIndIt, int &jacobNum, int &oldJacob);
	void 	initBounds(std::vector<int> tmpMain, std::vector<int> &bounds, int times);
	void 	initTmpMain(std::vector<int> &tmpMain,std::vector<int> mainInd,std::vector<int> bounds);
	int		findValinBounds(std::vector<int> bounds, int index);
	void	binaryInsert(std::vector<int> &mainInd, std::vector<int> &tmpMain, std::vector<int> bounds,int bound, int indToPlace);
	void	changeMainV(std::vector<int> tmpMain, int times);
};



#endif