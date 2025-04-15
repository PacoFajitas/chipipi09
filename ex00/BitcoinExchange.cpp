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


static std::string	trimStr(std::string& str)
{
	size_t start = str.find_first_not_of(" \t\r");
	size_t end = str.find_last_not_of(" \t\r\n");
	 if (start != std::string::npos)
       str = str.substr(start, end + start + 1);
	return (str);
}

static void initDate(tm& date)
{
	date.tm_gmtoff = 0;
	date.tm_hour = 0;
	date.tm_isdst = 0;
	date.tm_mday = 0;
	date.tm_min = 0;
	date.tm_mon = 0;
	date.tm_sec = 0;
	date.tm_wday = 0;
	date.tm_yday = 0;
	date.tm_year = 0;
	date.tm_zone = 0;
}
//returns true if valid, false if invalid
static bool checkValidDayMonth(int day, int month)
{

	if (((day > 28 || day < 0) && month == 2) ||((day > 31 || day < 0) && month != 2))
		return false;
	if(month < 0 || month > 12)
		return false;
	return true;
}

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

BitcoinExchange::BitcoinExchange()
{
	saveCsv();
}

void BitcoinExchange::saveCsv()
{
	std::string					date;
	std::string					rate;
	std::ifstream				base("data.csv");
	std::vector<std::string> 	dates;
	tm							finalDate;

	if (!base.is_open())
		throw std::runtime_error("Error opening exchange rates base.");
	if (!std::getline(base, date)) //skipping the first line with the header
		throw std::invalid_argument("Data base is empty.");
	if ( date.find_first_not_of(" \t\r") == std::string::npos)
		throw std::invalid_argument("Data base is empty.");
	
	while (std::getline(base, date, ',') && std::getline(base, rate))
	{
		initDate(finalDate);
		dates = splitString(date, "-");
		finalDate.tm_year = atoi(dates[0].c_str());
		finalDate.tm_mon = atoi(dates[1].c_str());
		finalDate.tm_mday = atoi(dates[2].c_str());
		data.insert(std::make_pair(finalDate,strtof(rate.c_str(), NULL)));
	}
	base.close();
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

float BitcoinExchange::calculateValues(tm date, float val)
{
	std::map<tm, float>::reverse_iterator	it = data.rbegin();
	while (it != data.rend())
	{
		tm baseDate = (*it).first;
		if (baseDate <= date)
			return ((*it).second * val);
		it++;
	}
	throw std::out_of_range("No records");
	
}

void BitcoinExchange::parseData(std::string input)
{
	std::string date;
	tm finalDate;
	float val;
	std::vector<std::string> splitDate;
	std::string value;
	initDate(finalDate);
	if(input.find('|') == std::string::npos || input.find('|') + 1 == input.length())
		throw BadFormatException();
	date = input.substr(0, input.find('|'));
	value = input.substr(input.find('|') + 1);
	if(date.find_first_not_of(" \t\r") == std::string::npos || value.find_first_not_of(" \t\r") == std::string::npos)
		throw BadFormatException();
	splitDate = splitString(date, "-");
	if (splitDate.size()!= 3)
		throw BadFormatException();
	for (size_t i = 0; i < splitDate.size(); i++)
	{
		splitDate[i] = trimStr(splitDate[i]);
	}
	for (size_t i = 0; i < splitDate.size(); i++)
	{
		for (size_t j = 0; j < splitDate[i].length(); j++)
		{
			if (!isdigit(splitDate[i][j]))
			{
				
				throw BadFormatException(date);
			}
		}
		
	}
	
	finalDate.tm_year = atoi(splitDate[0].c_str());
	if(!checkValidDayMonth(atoi(splitDate[2].c_str()) ,atoi(splitDate[1].c_str())))
	{
		std::cout << "holi" << std::endl;
		throw BadFormatException(date);
	}
	finalDate.tm_mon = atoi(splitDate[1].c_str());
	finalDate.tm_mday = atoi(splitDate[2].c_str());
	value = trimStr(value);
	for (size_t i = 0; i < value.length(); i++)
	{
		if(!isdigit(value[i]) && value[i] != '.')
		{
			throw BadValueException();
		}
	}
	val = strtof(value.c_str(), NULL);
	if (val > MAX_VAL || val < MIN_VAL)
		throw BadValueException();	
	outputData(calculateValues(finalDate, val), finalDate, val);
}

void BitcoinExchange::outputData(float value, tm date, float oldval)
{
	std::cout << date.tm_year << "-" << date.tm_mon << "-" << date.tm_mday;
	std::cout << " => " << oldval << " = " << value << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::btc(char *file)
{
	std::ifstream in(file);
	std::string linia;

	if(!in.is_open())
		throw std::runtime_error("Could not open file.");
	std::getline(in, linia);
	if(linia.empty() || linia.find_first_not_of(" \t\r") == std::string::npos)
		throw std::runtime_error("File is empty.");
	std::transform(linia.begin(), linia.end(), linia.begin(), ::tolower);
	linia = trimStr(linia);
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
    : mensaje("bad input") 
	{}

// Constructor con un argumento para la fecha
BitcoinExchange::BadFormatException::BadFormatException(const std::string& date)
    : _date(date), mensaje("bad input => " + date) {}

BitcoinExchange::BadFormatException::~BadFormatException() throw()
{
}

// Método what() para devolver el mensaje completo
const char* BitcoinExchange::BadFormatException::what() const throw() {
    return mensaje.c_str();
}


bool operator<=(const tm& lhs, const tm& rhs) {
    if (lhs.tm_year != rhs.tm_year) return lhs.tm_year < rhs.tm_year;
    if (lhs.tm_mon != rhs.tm_mon) return lhs.tm_mon < rhs.tm_mon;
    return lhs.tm_mday <= rhs.tm_mday;  // Comparación final solo con el día
}


bool operator<(const tm& lhs, const tm& rhs) {
    if (lhs.tm_year != rhs.tm_year) return lhs.tm_year < rhs.tm_year;
    if (lhs.tm_mon != rhs.tm_mon) return lhs.tm_mon < rhs.tm_mon;
    if (lhs.tm_mday != rhs.tm_mday) return lhs.tm_mday < rhs.tm_mday;
    if (lhs.tm_hour != rhs.tm_hour) return lhs.tm_hour < rhs.tm_hour;
    if (lhs.tm_min != rhs.tm_min) return lhs.tm_min < rhs.tm_min;
    return lhs.tm_sec < rhs.tm_sec;
}