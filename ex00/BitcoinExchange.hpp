/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:46 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/13 18:39:16 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <iostream>
# include <fstream>
# include <exception>
# include <vector>

# define MAX_VAL 1000
# define MIN_VAL 0

class BitcoinExchange
{
	private:
		class BadValueException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		class BadFormatException : public std::exception {
            private:
                std::string _date;
                std::string mensaje;

            public:
                BadFormatException();
                BadFormatException(const std::string& date);
				virtual ~BadFormatException() throw();
                const char* what() const throw();
        };
		BitcoinExchange(const BitcoinExchange& old);
		std::map<tm, float> data;
		BitcoinExchange& operator=(const BitcoinExchange& old);
		void	calculateValues(tm date, float val);
		void	parseData(std::string input);
	public:
		BitcoinExchange();
		~BitcoinExchange();
		void	btc(char* file);
};
#endif
