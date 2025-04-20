/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:48:08 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/21 01:48:10 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <iostream>
# include <vector>

class PmergeMe
{
private:
	std::vector<std::vector<int> > data;
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
	void	printVectorBase();
};



#endif