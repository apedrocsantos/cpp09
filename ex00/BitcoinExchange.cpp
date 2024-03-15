/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/15 11:14:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <limits>
#include <cfloat>
#include <sstream>
#include <fstream>
#include <string>

BitcoinExchange::BitcoinExchange(std::string input)
{
    std::string line;
    std::ifstream infile;
    infile.open(input);
    if (!infile)
    {
        std::cerr << "Error: could not open file.\n";
        return;
    }
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        addToList(line);
        if ((infile >> std::ws).eof())
            break;
    }
    infile.close();
    run();
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

float BitcoinExchange::stof(std::string string, bool date)
{
    (void) date;
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
    if (nb == 0 && date)
    {
        std::string error = "Error: bad input => " + this->_date;
        throw(std::invalid_argument(error));
    }
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
    this->_year = static_cast<int>(stof(string, 1));
    if (this->_year < 2009 || this->_year > 2022)
        throw(std::invalid_argument(error));
    std::getline(ss, string, '-');
    this->_month = static_cast<int>(stof(string, 1));
    if (this->_month < 1 || this->_month > 12)
        throw(std::invalid_argument(error));
    if (BitcoinExchange::leapYear(this->_year))
        days[2] = 29;
    std::getline(ss, string, '-');
    this->_day = static_cast<int>(stof(string, 1));
    if (this->_day < 1 || this->_day > days[this->_month])
        throw(std::invalid_argument(error));
    if (!ss.eof())
        throw(std::invalid_argument(error));
    std::getline(ss, string, '-');
}

void BitcoinExchange::checkValue(std::string value)
{
    if (stof(value, 0) > 1000)
        throw(std::out_of_range("Error: value too high."));
    this->_value = stof(value, 0);
}

bool BitcoinExchange::leapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

void BitcoinExchange::run()
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
            string.erase(0, string.find_first_not_of(' '));       
            string.erase(string.find_last_not_of(' ') + 1); 
            this->_date = string;
            checkDate(string);
            if (!ss.eof())
            {
                // VALUE
                std::getline(ss, string, '|');
                try
                {
                    checkValue(string);
                    calculate();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void BitcoinExchange::calculate()
{
    int year;
    int month;
    int day;
    float value;
    std::string line;
    std::string newline;
    std::ifstream infile;
    
    infile.open("data.csv");
    std::getline(infile, line);
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        std::getline(ss, line, ',');
        std::stringstream ss2(line);
        std::getline(ss2, newline, '-');
        year = static_cast<int>(BitcoinExchange::stof(newline, 1));
        std::getline(ss2, newline, '-');
        month = static_cast<int>(BitcoinExchange::stof(newline, 1));
        std::getline(ss2, newline, '-');
        std::getline(ss, line, ',');
        day = static_cast<int>(BitcoinExchange::stof(newline, 1));
        if (this->_year >= year)
        {
            if (this->_year == year && this->_month >= month)
            {
                if (this->_year == year && this->_month == month && this->_day >= day)
                    value = BitcoinExchange::stof(line, 0);
                else
                {
                    std::cout << this->_date << " => " << this->_value << " = " << this->_value * value << std::endl;
                    break;
                }
            }
        }
    }
}