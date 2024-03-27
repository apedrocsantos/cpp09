/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:30 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/27 11:32:14 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <climits>
#include <cfloat>
#include <sstream>
#include <fstream>
#include <string>
// #include <bits/stdc++.h>


BitcoinExchange::BitcoinExchange(std::string input)
{
    std::string line;
    std::ifstream infile;
    std::ifstream datafile;

    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    this->_cur_day = aTime->tm_mday;
    this->_cur_month = aTime->tm_mon + 1;
    this->_cur_year = aTime->tm_year + 1900;
    infile.open(input.c_str());
    datafile.open("data.csv");
    if (!infile || !datafile)
    {
        std::cerr << "Error: could not open file(s).\n";
        return;
    }
    datafile.close();
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

BitcoinExchange::BitcoinExchange(BitcoinExchange const &that)
{
    *this = that;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &that)
{
    if (this != &that)
    {
        this->_year = that._year;
        this->_month = that._month;
        this->_day = that._day;
        this->_date = that._date;
        this->_lst.clear();
        std::copy(that._lst.begin(), that._lst.end(), this->_lst.begin());
    }
    return (*this);
}

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
    float nb;
    int i = 0;
    std::stringstream ss;
    
    if (date)
    {
        if (string.find('.') != std::string::npos)
        {
            std::string error = "Error: bad input => " + this->_date;
            throw(std::invalid_argument(error));
        }
    }
    ss << string;
    if (ss.fail())
        throw(std::invalid_argument("Error: invalid number =>" + string));
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
        throw(std::invalid_argument("Error: bad input => " + this->_date));
    }
    if (nb == 0)
        throw(std::invalid_argument("Error: bad input => " + string));
    return (nb);
}

void BitcoinExchange::checkDate(std::string date)
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string string;
    std::string error = "Error: bad input => " + date;
    if (date.length() != 10)
        throw(std::invalid_argument(error));
    std::stringstream ss(date);
    std::getline(ss, string, '-');
    this->_year = static_cast<int>(stof(string, 1));
    if (this->_year < 2009)
        throw(std::invalid_argument(error));
    std::getline(ss, string, '-');
    if (string.length() != 2)
        throw(std::invalid_argument(error));
    this->_month = static_cast<int>(stof(string, 1));
    if (this->_month < 1 || this->_month > 12)
        throw(std::invalid_argument(error));
    if (BitcoinExchange::leapYear(this->_year))
        days[2] = 29;
    std::getline(ss, string, '-');
    if (string.length() != 2)
        throw(std::invalid_argument(error));
    this->_day = static_cast<int>(stof(string, 1));
    if (this->_day < 1 || this->_day > days[this->_month])
        throw(std::invalid_argument(error));
    if (!ss.eof())
        throw(std::invalid_argument(error));
    if (this->_year > this->_cur_year || (this->_year == this->_cur_year && this->_month > this->_cur_month) || (this->_year == this->_cur_year && this->_month == this->_cur_month && this->_day > this->_cur_day))
        throw(std::invalid_argument(error));
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
            else
                throw(std::invalid_argument("Error: bad input => " + this->_date));
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
        value = BitcoinExchange::stof(line, 0);
        if (this->_year < year || (this->_year == year && this->_month < month) || (this->_year == year && this->_month == month && this->_day <= day))
        {
            std::cout << this->_date << " => " <<this->_value << " = " << this->_value * value << std::endl;
            return;
        }
    }
    std::cout << this->_date << " => " <<this->_value << " = " << this->_value * value << std::endl;
}