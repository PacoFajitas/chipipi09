/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:48:08 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/16 20:07:04 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <iostream>
# include <random>
# include <vector>

class PmergeMe
{
private:
	std::vector<std::vector<int>> data;
public:
	PmergeMe();
	PmergeMe(PmergeMe &old);
	PmergeMe& operator=(PmergeMe& old);
	~PmergeMe();
};



#endif