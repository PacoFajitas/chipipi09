/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:46 by tfiguero          #+#    #+#             */
/*   Updated: 2025/04/16 21:16:50 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <iostream>
# include <fstream>
# include <exception>
# include <cstdlib>
# include <utility>
# include <algorithm>

# define MAX_VAL 10000
# define MIN_VAL 0

class BitcoinExchange
{
	private:
		void saveCsv();
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
		void splitDate(const std::string& str, const std::string& delimiter, tm &finalDate);
		std::map<tm, float> data;
		BitcoinExchange& operator=(const BitcoinExchange& old);
		float	calculateValues(tm date, float val);
		void	parseData(std::string input);
		void	outputData(float value, tm date, float oldval);
	public:
		BitcoinExchange();
		~BitcoinExchange();
		void	btc(char* file);
};
bool operator<=(const tm& lhs, const tm& rhs);
bool operator<(const tm& lhs, const tm& rhs);
#endif
