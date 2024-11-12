#include "BitcoinExchange.hpp"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero < tfiguero@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:44 by tfiguero          #+#    #+#             */
/*   Updated: 2024/11/12 16:41:44 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &old)
{
	*this = old;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &old)
{
	this->data = old.data;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}
