/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:02:48 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/07 18:47:11 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

//11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7 
int	main(int argc, char **argv)
{
	try
	{
		PmergeMe a(argc, argv);
		clock_t	init = clock();
		std::cout << "Before: " << std::endl;
		a.printVector();
		a.sortV();
		std::cout << "After: " << std::endl;
		a.printVector();
		clock_t	end = clock();
		double	vectorTime = ((end - init) / static_cast<double>(CLOCKS_PER_SEC)) * 1000;
		init = clock();
		a.sortD();
		end = clock();
		double	dequeTime = ((end - init) / static_cast<double>(CLOCKS_PER_SEC)) * 1000;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << vectorTime << " ms" << std::endl;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : " << dequeTime << " ms" << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}