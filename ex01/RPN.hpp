/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:43:20 by tfiguero          #+#    #+#             */
/*   Updated: 2024/09/29 16:40:54 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <cstdlib>
# include <stack>
# include <sstream>

class RPN
{
	class excpetionError : public std::exception
	{
		public:
			const char* what() const throw();
	};
	private:
		std::stack<int> _nums;
	public:
		RPN();
		RPN(const RPN& old);
		RPN& operator=(const RPN& old);
		~RPN();
		void evaluate(std::string arg);
		void calculate(char oper);
	
};

#endif