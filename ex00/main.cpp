/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:57 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/13 18:26:03 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char** argv)
{
	(void) argv;
	(void) argc;
	std::string test = "date | ";
	std::string testio2 = test.substr(test.find('|') + 1);
	 if(test.find('|') == test.length())
	 std::cout << "equisde" << std::endl;
	 	
	std::cout << testio2 << std::endl;
}