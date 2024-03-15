/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:21:32 by anda-cun          #+#    #+#             */
/*   Updated: 2024/03/15 11:14:29 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <vector>

class BitcoinExchange
{
    int _year;
    int _month;
    int _day;
    float _value;
    std::string _date;
    std::vector<std::string> _lst;
    
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