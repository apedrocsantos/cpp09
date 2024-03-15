/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/15 00:13:25 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <limits>
#include <cfloat>
#include <sstream>
#include <fstream>
#include <string>

BitcoinExchange::BitcoinExchange()
{
}

// BitcoinExchange::BitcoinExchange(BitcoinExchange const &that)
// {

// }

// BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &that)
// {

// }

BitcoinExchange::~BitcoinExchange()
{
    
}

void BitcoinExchange::addToList(std::string string)
{
    this->_lst.push_back(string);
}

void BitcoinExchange::getList()
{
    std::vector<std::string>::iterator it;
    for (it = this->_lst.begin(); it != this->_lst.end(); it++)
        std::cout << (*it) << std::endl;
}

float BitcoinExchange::stof(std::string string)
{
    float nb;
    int i = 0;
    std::stringstream ss;
    
    ss << string;
    ss >> nb;
    while (string[i] && string[i] == ' ')
        i++;
    if (string[i] == '0' && (!string[i + 1] || string[i + 1] == ' '))
        return (0);
    if (nb == INT_MAX)
        throw(std::out_of_range("Error: too large a number."));
    if (nb < 0)
        throw(std::invalid_argument("Error: not a positive number."));
    if (nb == 0)
        throw(std::invalid_argument("Error: invalid value."));
    return (nb);
}

void BitcoinExchange::checkDate(std::string date)
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string string;
    std::string error = "Error: bad input => " + date;
    std::stringstream ss(date);
    std::getline(ss, string, '-');
    this->_year = static_cast<int>(stof(string));
    if (this->_year < 2009 || this->_year > 2022)
        throw(std::invalid_argument(error));
    std::getline(ss, string, '-');
    this->_month = static_cast<int>(stof(string));
    if (this->_month < 1 || this->_month > 12)
        throw(std::invalid_argument(error));
    if (BitcoinExchange::leapYear(this->_year))
        days[2] = 29;
    std::getline(ss, string, '-');
    this->_day = static_cast<int>(stof(string));
    if (this->_day < 1 || this->_day > days[this->_month])
        throw(std::invalid_argument(error));
    if (!ss.eof())
        throw(std::invalid_argument(error));
    std::getline(ss, string, '-');
}

void BitcoinExchange::checkValue(std::string value)
{
    if (stof(value) > 1000)
        throw(std::out_of_range("Error: value too high."));
    this->_value = stof(value);
}

bool BitcoinExchange::leapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

void BitcoinExchange::calculate()
{
    std::string string;
    std::vector<std::string>::iterator it;
    for (it = this->_lst.begin(); it != this->_lst.end(); it++)
    {
        std::stringstream ss(*it);
        // DATE
        std::getline(ss, string, '|');
        try
        {
            checkDate(string);
            std::cout << this->_year << "-" << this->_month << "-" << this->_day << ": ";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        if (!ss.eof())
        {
            // VALUE
            std::getline(ss, string, '|');
            try
            {
                checkValue(string);
                std::cout << this->_value << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        getLine();
    }
}

void BitcoinExchange::getLine()
{
    // int year;
    // int month;
    // int day;
    // float value;
    std::string line;
    std::string newline;
    std::ifstream infile;
    
    infile.open("data.csv");
    std::getline(infile, line);
    while (std::getline(infile, line, ','))
    {
        if ((infile >> std::ws).eof())
            break;
        std::stringstream ss(line);
        std::getline(ss, newline, '-');
        std::cout << "y: " << newline << "\t";
        // year = static_cast<int>(BitcoinExchange::stof(newline));
        // std::cout << this->_year << "\t" << year << std::endl;
        std::getline(ss, newline, '-');
        std::cout << "m: " << newline << "\t";
        // month = static_cast<int>(BitcoinExchange::stof(newline));
        // std::cout << this->_month << "\t" << month << std::endl;
        std::getline(ss, newline, '-');
        std::cout << "d: " << newline << "\n";
        std::cout << line << std::endl;
        // day = static_cast<int>(BitcoinExchange::stof(newline));
        // std::cout << this->_day << "\t" << day << std::endl;
        // if (this->_year >= year && this->_month >= month && this->_day >= day)
        //     value = BitcoinExchange::stof(line);
        // else
        // {
        //     std::cout << "line: " << line << "\t" << value << std::endl;
        //     break;
        // }
    }
}