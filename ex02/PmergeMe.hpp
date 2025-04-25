/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:48:08 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/25 22:27:01 by tfiguero         ###   ########.fr       */
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
	void makePairs(int depth, size_t times);
	void binarySort(size_t times);
	int nextJacobstahl(int current);
};



#endif