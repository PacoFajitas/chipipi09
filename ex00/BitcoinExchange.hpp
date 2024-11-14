/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:46 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/14 23:08:27 by tfiguero         ###   ########.fr       */
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
# include <cstdlib>
# include <utility>
# include <algorithm>

# define MAX_VAL 1000
# define MIN_VAL 0

class BitcoinExchange
{
	private:
		bool checkValidDate(std::vector<std::string> date);
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
