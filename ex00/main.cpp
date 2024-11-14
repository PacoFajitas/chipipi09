/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:57 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/14 22:42:10 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


int	main(int argc, char** argv)
{
    BitcoinExchange	mybtc;
	
	try {
		if (argc != 2) 
			throw std::invalid_argument("Invalid number of arguments. Introduce one agrument [exchanges file]");
	//	std::string		file = av[1];
		mybtc.btc(argv[1]);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}