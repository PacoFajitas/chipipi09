/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:02:48 by tfiguero          #+#    #+#             */
/*   Updated: 2025/05/02 13:15:50 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

int	main(int argc, char **argv)
{
	RPN a;
	std::string b;
	if (argc == 2)
	{
		b = argv[1];
		try
		{
			a.evaluate(b);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	return 0;
}