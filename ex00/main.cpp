/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:57 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/13 18:45:01 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        std::string token = str.substr(start, end - start);
        if (!token.empty()) {  // Ignora los tokens vacíos
            tokens.push_back(token);
        }
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    // Agregar la última parte si no está vacía
    std::string token = str.substr(start);
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}
int	main(int argc, char** argv)
{
	(void) argv;
	(void) argc;
	std::vector<std::string> test3;
	std::string date = "    2011-01-03     ";
	// std::string testio2 = test.substr(test.find('|') + 1);
	//  if(test.find('|') == test.length())
	//  std::cout << "equisde" << std::endl;
	int i =0;
	date = date.substr(date.find_first_not_of(' '));
	date = date.substr(0, date.find_last_not_of(' ') + 1);
	test3= splitString(date, "-");
	while(i < 3)
	{
	  std::cout << test3[i] << std::endl;
	  i++;
	}
}