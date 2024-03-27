/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:32 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/27 15:07:47 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <list>

class BitcoinExchange
{
    int _year;
    int _month;
    int _day;
    int _cur_year;
    int _cur_month;
    int _cur_day;
    float _value;
    std::string _date;
    std::list<std::string> _lst;
    
    float stof(std::string string, bool date);
    void checkDate(std::string date);
    void checkValue(std::string value);
    bool leapYear(int year);
    void calculate();
    BitcoinExchange();
    
    public:
    BitcoinExchange(std::string input);
    BitcoinExchange(BitcoinExchange const &that);
    BitcoinExchange &operator=(BitcoinExchange const &that);
    ~BitcoinExchange();
    void addToList(std::string string);
    void getList();
    void run();
};

#endif