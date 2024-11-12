/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:46 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/12 17:15:18 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <iostream>

# define MAX_VAL 1000
# define MIN_VAL 0

class BitcoinExchange
{
	private:
		std::map<tm, float> data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& old);
		BitcoinExchange& operator=(const BitcoinExchange& old);
		void	calculateValues(tm date, float val);
		~BitcoinExchange();
};
		void	parseData(std::string input);
#endif
