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

void BitcoinExchange::calculateValues(tm date, float val)
{
}

void BitcoinExchange::parseData(std::string input)
{
	std::string date;
	std::string value;

	if(input.find('|') == std::string::npos || input.find('|') + 1 == input.length())
		throw BadFormatException();
	date = input.substr(0, input.find('|'));
	value = input.substr(input.find('|') + 1);
	if(date.find_first_not_of(' ') == std::string::npos || value.find_first_not_of(' ') == std::string::npos)
		throw BadFormatException();
	
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::btc(char *file)
{
	std::ifstream in(file);
	std::string linia;

	if(!in.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::getline(in, linia);
	if(linia.compare("date | value"))
		throw BitcoinExchange::BadFormatException();
	while (std::getline(in, linia))
	{
		try
		{
			parseData(linia);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: "<< e.what() << '\n';
		}
		
	}
	
	
}

const char *BitcoinExchange::BadValueException::what() const throw()
{
	return "not a positive number";
}

// Constructor sin argumentos
BitcoinExchange::BadFormatException::BadFormatException()
    : mensaje("bad input") {}

// Constructor con un argumento para la fecha
BitcoinExchange::BadFormatException::BadFormatException(const std::string& date)
    : _date(date), mensaje("bad input => " + date) {}

// Método what() para devolver el mensaje completo
const char* BitcoinExchange::BadFormatException::what() const throw() {
    return mensaje.c_str();
}